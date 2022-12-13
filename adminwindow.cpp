#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "loginwindow.h"
#include "dbmanager.h"
#include "addmember.h"
#include "additem.h"
#include "edititem.h"
#include "deleteitem.h"
#include "deletemember.h"
#include "changemember.h"
AdminWindow::AdminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_pushButton_4_clicked()
{
    LoginWindow *login = new LoginWindow;
    this->close();
    login->show();
}





void AdminWindow::on_pushButton_9_clicked() // load button for items
{
    DbManager db("C:/Users/13109/Desktop/database/bulkclubdb.db");
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from inventory");
    ui->tableView_3->setModel(model);
}


void AdminWindow::on_pushButton_10_clicked() // load members
{
    DbManager db("C:/Users/13109/Desktop/database/bulkclubdb.db");
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select member_name, membership_number, membership_type, membership_expiration from members");
    ui->tableView->setModel(model);

}


void AdminWindow::on_pushButton_6_clicked() //add item
{
    addmember dialog;
    dialog.setModal(true);
    dialog.exec();
}

void AdminWindow::on_pushButton_clicked() // add member
{
    addItem dialog;
    dialog.setModal(true);
    dialog.exec();
}


void AdminWindow::on_pushButton_8_clicked() // edit items
{
    editItem dialog;
    dialog.setModal(true);
    dialog.exec();
}


void AdminWindow::on_pushButton_7_clicked() // delete items
{
    deleteItem dialog;
    dialog.setModal(true);
    dialog.exec();
}


void AdminWindow::on_pushButton_2_clicked() // delete member
{
    deleteMember dialog;
    dialog.setModal(true);
    dialog.exec();
}


void AdminWindow::on_pushButton_3_clicked() //load executives that could be upgraded
{
    DbManager db("C:/Users/13109/Desktop/database/bulkclubdb.db");
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select member_name, membership_number, membership_type, total_spent from members where total_spent * 0.02 < 120.00 and membership_type = 'Executive'");
    ui->tableView_2->setModel(model);
}


void AdminWindow::on_pushButton_5_clicked() // change membership type
{
    changemember dialog;
    dialog.setModal(true);
    dialog.exec();
}


void AdminWindow::on_pushButton_11_clicked() // loads regulars that could  be upgraded
{
    DbManager db("C:/Users/13109/Desktop/database/bulkclubdb.db");
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select member_name, membership_number, membership_type, total_spent from members where total_spent * 0.02 > 55.00 and membership_type = 'Regular'");
    ui->tableView_2->setModel(model);
}

