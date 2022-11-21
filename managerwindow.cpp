#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "loginwindow.h"

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

void ManagerWindow::on_pushButton_7_clicked()
{
    LoginWindow *login = new LoginWindow;
    this->close();
    login->exec();
}

