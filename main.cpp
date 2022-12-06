#include "loginwindow.h"
#include "adminwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow login;
    login.show();

    return a.exec();
}
