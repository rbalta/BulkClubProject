#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "adminwindow.h"
#include "managerwindow.h"
#include "dbmanager.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setFixedSize(650,350);
    ui->lineEdit->setAlignment(Qt::AlignHCenter);
    ui->lineEdit_2->setAlignment(Qt::AlignHCenter);
    ui->lineEdit->setPlaceholderText("User ID");
    ui->lineEdit_2->setPlaceholderText("Password");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked() // Login button
{
    DbManager db("C:/Users/13109/Desktop/database/bulkclubdb.db");
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if(db.idMatch(username)) // check user loop
    {
        if (db.passwordCheck(username, password)) // check pass loop
        {
            QString access = db.accessCheck(username);
            if (access == "employee") // check access level loop
            {
                MainWindow *main = new MainWindow;
                this->hide();
                main->show();
            }
            else if (access == "manager")
            {
                ManagerWindow *m = new ManagerWindow;
                this->hide();
                m->show();
            }
            else if (access == "admin")
            {
                AdminWindow *a = new AdminWindow;
                this->hide();
                a->show();
            }
            else
                QMessageBox::warning(this, tr("Error"),
                    access);
        }
        else
        {
            QMessageBox::information(this, tr("Error"),
                tr("Invalid password."));
        }
    }
    else
    {
        QMessageBox::information(this, tr("Error"),
            tr("Username does not exist."));
    }
}

void LoginWindow::on_pushButton_2_clicked() // forgot password button
{
    QMessageBox::information(this, tr("Help"),
            tr("Please contact an administrator to reset your password."));
}

void LoginWindow::closeEvent(QCloseEvent *event) // confirms exit from login screen
{
    QMessageBox::StandardButton quitConfirm = QMessageBox::Yes;

    quitConfirm = QMessageBox::question(this, "Bulk Club",
                                    tr("Are you sure you want to quit?\n"),
                                    QMessageBox::No | QMessageBox::Yes);

    if (quitConfirm == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}
