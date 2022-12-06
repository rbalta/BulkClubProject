#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "loginwindow.h"
#include "dbmanager.h"

ManagerWindow::ManagerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::on_logout_clicked()
{
    LoginWindow *login = new LoginWindow;
    this->close();
    login->exec();
}

// A store manager should be able to display a sales report for any
// given day. It should include a list of items and quantities sold on that
// day as well names of the members who shopped that day.  Display
// the total revenue (including tax) for the given day.  It should also
// include number of unique Executive members and Regular
// members who shopped during the given day.

void ManagerWindow::on_pushButton_clicked() {
    //open database
    DbManager db("C:/Users/bounc/Documents/GitHub/BulkClubProject/bulkclubdb.db");

    QSqlQuery qryReport;
    QString qryRev;
    QString qryExe;

    //read from text editor
    QString purchase_date = ui->lineEdit->text();
    qryReport = db.qryDailyReport(purchase_date);
    qryRev = db.calcDailyReportRev("1 gallon of milk");
    qryExe = db.calcDailyReportExecutive(purchase_date);

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery(std::move(qryReport));
    ui->tableView->setModel(model);

    qDebug() << "Your mom: " + qryRev;
    qDebug() << "is a very nice woman " + qryExe;

    ui->textBrowser_2->setText(qryRev);
    ui->textBrowser_3->setText(qryExe);
}

// A store manager should be able to display the total purchases for
// each member including tax sorted by membership number.  The
// display should also include a grand total including tax of all the
// purchases for all the members.
// A store manager should be able to enter a membership number or
// name and display the total purchases including tax for that member.
//void DbManager::qryMemberPurchases(QString membership_number, QString membership_name);
void ManagerWindow::on_pushButton_8_clicked() {
    //open database
    DbManager db("C:/Users/bounc/Documents/GitHub/BulkClubProject/bulkclubdb.db");

    QSqlQuery qryMemReport;

    //read from text editor
    QString membership_number = ui->lineEdit_2->text();

    qryMemReport = db.qryMemberReport(membership_number);

    qDebug() << qryMemReport.value(0);

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery(std::move(qryMemReport));

    ui->tableView_10->setModel(model);

}

// A store manager should be able to display the quantity of each item
// sold sorted by item name and the total revenue (without tax) for
// each item.
// A store manager should be able to enter an item name and only
// display the quantity of that item sold as well as the total revenue
// (without tax) for the item.  No other items should be displayed.


// A store manager should be able to display the rebate of all the
// Executive members sorted by membership number. Rebates are
// based on purchases before tax.
//void DbManager::calcRebate();

// A store manager should be able to enter a month and obtain a
// display of all members whose memberships expire that month as
// well as the cost to renew their memberships.
//void DbManager::qryMembershipExp(QString membership_expiration);



