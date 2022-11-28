#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "loginwindow.h"

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

