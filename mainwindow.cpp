#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "dbmanager.h"

const double SALES_TAX = .0775;
const double EXEC_CASHBACK = 0.02;
QStringList selectedItems;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    DbManager db("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");
    ui->setupUi(this);

    // format for inventory display
    ui->tableView->setModel(db.pullInventoryItems());
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(3);
    ui->tableView->setColumnWidth(0, 350);

    // format for member display
    ui->memDisplay->horizontalHeader()->hide();
    ui->memDisplay->verticalHeader()->hide();

    // format for price totals display
    ui->tableWidget->setColumnWidth(0, 300);
    ui->tableWidget->verticalHeader()->setFixedSize(230, 180);
    ui->tableWidget->horizontalHeader()->hide();

    // set timestamp
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    // used as a blank table model
    ui->tableView_3->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    LoginWindow *login = new LoginWindow;
    login->show();
    this->close();
}


void MainWindow::on_pushButton_2_clicked()
{
    LoginWindow *login = new LoginWindow;
    this->close();
    login->show();
}


void MainWindow::on_pushButton_3_clicked() // check member number and show info if exists
{
    DbManager db("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");
    int memberId = ui->lineEdit->text().toInt();
    bool isValid = db.memberExists(memberId);

    if (isValid)
    {
        QSqlQueryModel *model = new QSqlQueryModel;

        model->setQuery(db.pullMemberInfo(memberId));

        ui->memDisplay->showRow(0);
        ui->memDisplay->setModel(model);
        ui->memDisplay->setColumnWidth(0, 275);
        ui->memDisplay->setRowHeight(0, 75);
    }
    else
    {
        ui->memDisplay->hideRow(0);
        QMessageBox::information(
            this, tr("Error"),
            tr("Member not found.") );
    }
}

void MainWindow::keyPressEvent(QKeyEvent* memLookup) // use Enter key to member lookup
{
    if(memLookup->key() == Qt::Key_Return)
        on_pushButton_3_clicked();
}

void MainWindow::updateTransactionTotals()
// updates transaction totals for when transaction table changes
{
    if (ui->tableView_2->model() == NULL)
    {
        ui->tableWidget->clearContents();
        return;
    }

    double price = 0;
    int quantity = 0;
    double totalBeforeTax = 0;
    double taxAmount = 0;

    for (int i = 0; i < ui->tableView_2->model()->rowCount(); i++)
    {
       quantity = ui->tableView_2->model()->index(i,2).data().toInt();
       price = ui->tableView_2->model()->index(i,1).data().toDouble();
       totalBeforeTax += (price * quantity);
    }
    taxAmount = QString::number((totalBeforeTax * SALES_TAX), 'f', 2).toDouble();

    QTableWidgetItem *ptr = new QTableWidgetItem;
    QTableWidgetItem *ptr2 = new QTableWidgetItem;
    QTableWidgetItem *ptr3 = new QTableWidgetItem;

    ptr->setData(Qt::EditRole, totalBeforeTax);
    ui->tableWidget->setItem(0, 0, ptr);

    ptr2->setData(Qt::EditRole, taxAmount);
    ui->tableWidget->setItem(1, 0, ptr2);

    ptr3->setData(Qt::EditRole, totalBeforeTax+taxAmount);
    ui->tableWidget->setItem(2, 0, ptr3);
}

void MainWindow::on_tableView_doubleClicked() // adds items to transaction window
{
    DbManager db("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");
    QAbstractItemModel *item = ui->memDisplay->model();

    if (item == NULL) // checks if a member ID has been added first
    {
        QMessageBox::warning(this, "Transaction",
                                tr("Please enter a member ID."));
        return;
    }

    ui->lineEdit->setReadOnly(true); // disables editing member num while transaction in progress

    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndexList list = selection->selectedIndexes();

    QString q = list.at(0).data().toString();
    selectedItems.append(q);

    ui->tableView_2->setModel(db.pullSelectedInventory(selectedItems));
    ui->tableView_2->show();
    ui->tableView_2->setColumnWidth(0, 250);

    updateTransactionTotals(); // runs the update function for cash totals
}

void MainWindow::on_pushButton_4_clicked() // checkout button
{
    DbManager db("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");

    updateTransactionTotals();

    int memNum = ui->lineEdit->text().toInt();
    double price = ui->tableWidget->item(0, 0)->text().toDouble();
    double totalBeforeTax = ui->tableWidget->item(0, 0)->text().toDouble();
    QDate currentDate = ui->dateTimeEdit->date();
    QStringList items;
    QList<int> quantities;
    QAbstractItemModel *model = ui->tableView_2->model();

    for (int i = 0; i < model->rowCount(); i++)
    {
        items.append(model->index(i, 0).data().toString());
        quantities.append(model->index(i, 2).data().toInt());
    }

    db.addToMemberTotal(memNum, price);
    if (ui->memDisplay->model()->index(0, 2).data().toString() == "Executive")
        db.addToExecCashback(memNum, totalBeforeTax, EXEC_CASHBACK);
    db.addTransaction(currentDate.toString("MM/dd/yyyy"), memNum, items, quantities);

    QMessageBox::information(this, "Transaction",
                             tr("Checkout complete!"));

    QAbstractItemModel *blankModel = ui->tableView_3->model();
    ui->tableView_2->setModel(blankModel);
    updateTransactionTotals();
    ui->lineEdit->setReadOnly(false); // enables editing after transaction done
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_6_clicked() // delete cart button
{
    QMessageBox::StandardButton deleteConfirm = QMessageBox::Yes;

    deleteConfirm = QMessageBox::question(this, "Transaction",
                        tr("Are you sure you want to delete this cart?\n"),
                        QMessageBox::No | QMessageBox::Yes);
    if (deleteConfirm == QMessageBox::Yes)
    {
        QAbstractItemModel *model = ui->tableView_3->model();

        ui->tableView_2->setModel(model);
        ui->tableWidget->clearContents();
        selectedItems.clear();
        ui->lineEdit->setReadOnly(false);
    }
    else
        return;
}
