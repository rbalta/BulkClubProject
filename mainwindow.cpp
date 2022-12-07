#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "dbmanager.h"

DbManager dbase("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");
const float SALES_TAX = .0775;
const float EXEC_CASHBACK = 0.02;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // format for inventory display
    ui->tableView->setModel(dbase.pullInventoryItems());
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
    int memberId = ui->lineEdit->text().toInt();
    bool isValid = dbase.memberExists(memberId);

    if (isValid)
    {
        QSqlQueryModel *model = new QSqlQueryModel;

        model->setQuery(dbase.pullMemberInfo(memberId));

        ui->memDisplay->showRow(0);
        ui->memDisplay->setModel(model);
        ui->memDisplay->setColumnWidth(0, 275);
        ui->memDisplay->setRowHeight(0, 75);
        ui->memDisplay->hideColumn(3);
        ui->memDisplay->hideColumn(4);
        ui->memDisplay->hideColumn(5);
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
        return;

    float price = 0;
    // int quantity = 0;
    float totalBeforeTax = 0;
    float taxAmount = 0;

    for (int i = 0; i < ui->tableView_2->model()->rowCount(); i++)
    {
       // quantity = ui->tableView_2->model()->index(i,2).data().toInt();
       price = ui->tableView_2->model()->index(i,1).data().toFloat();
       totalBeforeTax += (price);

    }
    taxAmount = totalBeforeTax * SALES_TAX;

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


void MainWindow::on_fruitButton_clicked() // button filters for inventory NOT WORKING YET
{
    ui->tableView->show();
    QSortFilterProxyModel *filter = new QSortFilterProxyModel;
    filter->setSourceModel(ui->tableView->model());

    filter->setFilterRegularExpression("fruit");
    filter->setFilterKeyColumn(3);
}

void MainWindow::on_tableView_doubleClicked() // adds items to transaction window
{
    QAbstractItemModel *item = ui->memDisplay->model();
    if (item == NULL) // checks if a member ID has been added first
    {
        QMessageBox::warning(this, "Transaction",
                                tr("Please enter a member ID."));
        return;
    }

    ui->lineEdit->setReadOnly(true); // disables editing member num while transaction in progress

    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QAbstractItemModel *fromModel = ui->tableView->model();
    QModelIndexList list = selection->selectedIndexes();
    QString q = list.at(0).data().toString();

    QAbstractItemModel *model = ui->tableView->model();
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel;
    proxy->setSourceModel(model);
    proxy->setFilterRegularExpression(q);
    proxy->setFilterKeyColumn(0);

    const int rows = fromModel->rowCount();
    QVariant quantity = 1;

    for (int i = 0; i < rows; i++)
    {
        fromModel->index(i, 2).data().setValue(quantity);
    }
    ui->tableView_2->setModel(fromModel);
    ui->tableView_2->hideColumn(3);
    ui->tableView_2->setColumnWidth(0, 275);

    updateTransactionTotals(); // runs the update function for cash totals
}

void MainWindow::on_pushButton_4_clicked() // checkout button
{
    int memNum = ui->lineEdit->text().toInt();
    double price = ui->tableWidget->item(0, 0)->text().toDouble();
    double totalBeforeTax = ui->tableWidget->item(0, 0)->text().toDouble();
    QDate currentDate = ui->dateTimeEdit->date();
    QStringList items;
    QList<int> quantities;

    dbase.addToMemberTotal(memNum, price);
    if (ui->tableWidget->item(0, 2)->text() == "Executive")
        dbase.addToExecCashback(memNum, totalBeforeTax, EXEC_CASHBACK);
    dbase.addTransaction(currentDate, memNum, items, quantities);

    QAbstractItemModel *model = ui->tableView_3->model();
    ui->tableView_2->setModel(model);
    updateTransactionTotals();
    ui->lineEdit->setReadOnly(false); // enables editing after transaction done
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
        ui->lineEdit->setReadOnly(false);
    }
    else
        return;
}
