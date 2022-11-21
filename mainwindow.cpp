#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"

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
    login->exec();
    this->close();
}


void MainWindow::on_pushButton_2_clicked()
{
    LoginWindow *login = new LoginWindow;
    this->close();
    login->exec();
}

