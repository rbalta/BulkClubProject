#include "mainwindow.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main;
    LoginWindow login;

    login.show();

    return a.exec();
}
