#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "loginwindow.h"
#include "dbmanager.h"
#include "addmember.h"
#include "additem.h"
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
    login->exec();
}





void AdminWindow::on_pushButton_9_clicked() // load button for items
{
    DbManager db("C:/Users/bounc/Documents/GitHub/BulkClubProject/bulkclubdb.db");
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from inventory");
    ui->tableView_3->setModel(model);

}


void AdminWindow::on_pushButton_10_clicked() // load members
{
    DbManager db("C:/Users/bounc/Documents/GitHub/BulkClubProject/bulkclubdb.db");
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from members");
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

