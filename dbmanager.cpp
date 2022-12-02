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
void DbManager::editItemPrice(QString item_name, QString sales_price)
{
    QSqlQuery qry;
    qry.prepare("update inventory set sales_price='"+sales_price+"' where item_name='"+item_name+"'");
    if (qry.exec())
    {
        QMessageBox msg;
        msg.setText("Item Updated");
        msg.exec();
    }
    else
    {

        QMessageBox msg;
        msg.setText("Failed to Update Item");
        msg.exec();
    }
}
void DbManager::deleteItem(QString item_name)
{
    QSqlQuery qry;
    qry.prepare("Delete from inventory where item_name='"+item_name+"'");
    if (qry.exec())
    {
        QMessageBox msg;
        msg.setText("Item Deleted");
        msg.exec();
    }
    else
    {

        QMessageBox msg;
        msg.setText("Failed to Delete Item");
        msg.exec();
    }
}
void DbManager::deleteMember(QString membership_number)
{
    QSqlQuery qry;
    qry.prepare("Delete from members where membership_number='"+membership_number+"'");
    if (qry.exec())
    {
        QMessageBox msg;
        msg.setText("Member Deleted");
        msg.exec();
    }
    else
    {

        QMessageBox msg;
        msg.setText("Failed to Delete Member");
        msg.exec();
    }
}

// Your team should provide an option to generate the sales report
// (including tax) for any given day by membership type.
void generateSalesReport(QString dayGiven);

// A store manager should be able to display the total purchases for
// each member including tax sorted by membership number.  The
// display should also include a grand total including tax of all the
// purchases for all the members.
void queryTotalPurchases();

// A store manager should be able to display the quantity of each item
// sold sorted by item name and the total revenue (without tax) for
// each item.
void queryQuantity();

// A store manager should be able to display the rebate of all the
// Executive members sorted by membership number. Rebates are
// based on purchases before tax.
void calcRebate();

// A store manager should be able to enter a month and obtain a
// display of all members whose memberships expire that month as
// well as the cost to renew their memberships.
void queryMembershipExp(int month) {
    QSqlQuery query;
    query.bindValue(":membership_expiration", month);

    if (query.exec())
    {
        QSqlQuery query("SELECT * FROM people");
        int idName = query.record().indexOf("name");
        while (query.next())
        {
           QString name = query.value(idName).toString();
           qDebug() << name;
        }
       if (query.next())
       {

       }
    }
}

// A store manager should be able to display the quantity of each item
// sold sorted by item name and the total revenue (without tax) for
// each item.
void queryItemQuant(QString itemName) {
    QSqlQuery query;
    query.bindValue(":quantitiy", itemName);

    if (query.exec())
    {
       if (query.next())
       {
          // it exists
       }
    }
}

// A store manager should be able to display the total purchases for
// each member including tax sorted by membership number.  The
// display should also include a grand total including tax of all the
// purchases for all the members.
void queryMemberPurchases(int memNum, QString memName);
