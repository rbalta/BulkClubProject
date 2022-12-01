#include "dbmanager.h"
#include <QMessageBox>

DbManager::DbManager(const QString& path)
{
    main_db = QSqlDatabase::addDatabase("QSQLITE");
    main_db.setDatabaseName(path);

    if (main_db.open())
        qDebug() << "Database connected.";
    else
        qDebug() << "Error: Database not found.";

}
void DbManager::addItem(QString item_name, QString sales_price)
{
    QSqlQuery qry;
    qry.prepare("insert into inventory (item_name,sales_price) values ('"+item_name+"','"+sales_price+"')");
    if (qry.exec())
    {
        QMessageBox msg;
        msg.setText("Item Added");
        msg.exec();
    }
    else
    {

        QMessageBox msg;
        msg.setText("Failed to Add Item");
        msg.exec();
    }
}
void DbManager::addMember(QString member_name, QString membership_number, QString membership_type, QString membership_expiration)
{
    QSqlQuery qry;
    qry.prepare("insert into members (member_name,membership_number,membership_type,membership_expiration) values ('"+member_name+"','"+membership_number+"','"+membership_type+"','"+membership_expiration+"')");
    if (qry.exec())
    {
        QMessageBox msg;
        msg.setText("Member Added");
        msg.exec();
    }
    else
    {

        QMessageBox msg;
        msg.setText("Failed to Add Member");
        msg.exec();
    }
}

