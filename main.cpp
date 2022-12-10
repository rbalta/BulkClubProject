#include "loginwindow.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //LoginWindow login;
    //login.show();

    MainWindow main;
    main.show();

    return a.exec();
}
