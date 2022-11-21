#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "adminwindow.h"
#include "managerwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setFixedSize(650,400);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked() // Login button
{
    if (ui->textEdit->toPlainText() == "employee")
    {
        MainWindow *main = new MainWindow;
        this->hide();
        main->showMaximized();
    }
    else if (ui->textEdit->toPlainText() == "manager")
    {
        ManagerWindow *m = new ManagerWindow;
        this->hide();
        m->showMaximized();
    }
    else if (ui->textEdit->toPlainText() == "admin")
    {
        AdminWindow *a = new AdminWindow;
        this->hide();
        a->showMaximized();
    }
    else
    {
        QMessageBox::information(
            this,
            tr("Error"),
            tr("Invalid ID or password.") );
    }
}

void LoginWindow::on_pushButton_2_clicked() // Admin button
{
    QString styleSheet = "background-color: rgba(230, 100, 77, 100); "
                         "color: rgb(255, 255, 255); "
                         "font: 16pt 'Segoe UI';";
    ui->textBrowser->setText("Admin Login");
    ui->textBrowser->setStyleSheet(styleSheet);
    ui->textBrowser->setAlignment(Qt::AlignCenter);
}

void LoginWindow::keyPressEvent(QKeyEvent* login) // use Enter key to also login
{
    if(login->key() == Qt::Key_Return)
        on_pushButton_clicked(); // doesn't work yet
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
