#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "dbmanager.h"

DbManager db("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTabSettings()
{
    ui->tabWidget->setAutoFillBackground(true);
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


bool MainWindow::on_pushButton_3_clicked()
{
    int number = ui->lineEdit->text().toInt();
    bool isExec;
    bool isValid = db.memberExists(number, isExec);

    if (isValid)
    {

    }
    return isExec;
}
