#include "loginwindow.h"
#include "adminwindow.h"
#include "managerwindow.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    LoginWindow login;
//    login.show();

//    MainWindow main;
//    main.show();

    ManagerWindow manager;
    manager.show();

    return a.exec();
}
