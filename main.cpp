#include "loginwindow.h"
#include "adminwindow.h"
#include "dbmanager.h"
#include "managerwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ManagerWindow manager;
    manager.show();

//     AdminWindow admin;
//     admin.show();
    // LoginWindow login;
    // login.show();

    return a.exec();
}
