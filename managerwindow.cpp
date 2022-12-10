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
    //read from text editor
    QString purchase_date = ui->lineEdit->text();
    DbManager datab("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");

    //create model
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery(datab.qryDailyReport(purchase_date));
    ui->tableView->setModel(model);

    //set values to text browsers
    ui->textBrowser_2->setText(datab.calcDailyReportRev(purchase_date));
    ui->textBrowser_3->setText(datab.calcDailyReportExecutive(purchase_date));
    ui->textBrowser_4->setText(datab.calcDailyReportRegular(purchase_date));
}

// A store manager should be able to display the total purchases for
// each member including tax sorted by membership number.  The
// display should also include a grand total including tax of all the
// purchases for all the members.
// A store manager should be able to enter a membership number or
// name and display the total purchases including tax for that member.
void ManagerWindow::on_pushButton_8_clicked() {
    //read from text editor
    QString membership_number = ui->lineEdit_2->text();
    DbManager datab("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery(datab.qryMemberReport(membership_number));
    ui->tableView_10->setModel(model);

    ui->textBrowser_5->setText(datab.calcMemberReportRev(membership_number));
}

// A store manager should be able to display the quantity of each item
// sold sorted by item name and the total revenue (without tax) for
// each item.
// A store manager should be able to enter an item name and only
// display the quantity of that item sold as well as the total revenue
// (without tax) for the item.  No other items should be displayed.
void ManagerWindow::on_pushButton_2_clicked() {
    //read from text editor
    QString item_name = ui->lineEdit_3->text();
    DbManager datab("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery(datab.qryItemReport(item_name));
    ui->tableView_3->setModel(model);

    ui->textBrowser_6->setText(datab.qryItemRevenue(item_name));
}

// A store manager should be able to display the rebate of all the
// Executive members sorted by membership number. Rebates are
// based on purchases before tax.
void ManagerWindow::on_pushButton_3_clicked() {
    //read from text editor
    QString membership_expiration = ui->lineEdit_4->text();
    DbManager datab("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery(datab.qryRebate());

    ui->tableView_4->setModel(model);
}

// A store manager should be able to enter a month and obtain a
// display of all members whose memberships expire that month as
// well as the cost to renew their memberships.
void ManagerWindow::on_pushButton_7_clicked() {
    //read from text editor
    QString membership_expiration = ui->lineEdit_4->text();
    DbManager datab("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery(datab.qryMemberExp(membership_expiration));

    ui->tableView_9->setModel(model);
}


