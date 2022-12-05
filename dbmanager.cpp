#include "dbmanager.h"
#include <QMessageBox>

DbManager::DbManager(const QString& path)
{
    main_db = QSqlDatabase::addDatabase("QSQLITE");
    main_db.setDatabaseName("C:/Users/13109/Desktop/database/bulkclubdb.db");

    if (main_db.open())
        qDebug() << "Database connected.";
    else
        qDebug() << "Error: Database not found.";

}

// AdminWindow functions
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

// ManagerWindow functions

// A store manager should be able to display a sales report for any
// given day. It should include a list of items and quantities sold on that
// day as well names of the members who shopped that day.  Display
// the total revenue (including tax) for the given day.  It should also
// include number of unique Executive members and Regular
// members who shopped during the given day.
QSqlQuery DbManager::qryDailyReport(QString purchase_date) {
    //set query
    QSqlQuery qry(main_db);
    qry.prepare("select purchase_date, item_name, quantity_purchased, member_name from sales, members where purchase_date=(:purchase_date)");
    qry.bindValue(":purchase_date",purchase_date);
    qry.exec();

    return qry;
}

QString DbManager::calcDailyReportRev(QString purchase_date) {
    QSqlQuery qry(main_db);
    qry.prepare("sum(quantity_purchased.sales*sales_price.inventory) as total_price.inventory from sales inner join inventory where purchase_date=(:purchase_date)");
    qry.bindValue(":purchase_date",purchase_date);
    qry.exec();

    qDebug() << qry.value(0).toString();

    return qry.value(0).toString();
}

QString DbManager::calcDailyReportExecutive(QString purchase_date) {
    QSqlQuery qry(main_db);
    qry.prepare("select count(membership_type) from members, sales where purchase_date=(:purchase_date)");
    qry.bindValue(":purchase_date",purchase_date);
    qry.exec();

    qDebug() << qry.value(0).toString();

    return qry.value(0).toString();
}

// A store manager should be able to display the total purchases for
// each member including tax sorted by membership number.  The
// display should also include a grand total including tax of all the
// purchases for all the members.
// A store manager should be able to enter a membership number or
// name and display the total purchases including tax for that member.
QSqlQuery DbManager::qryMemberReport(QString membership_number) {
    //set query
    QSqlQuery qry(main_db);

    qry.prepare("select membership_number, item_name, quantity_purchased, sales_price from sales, inventory where membership_number=(:membership_number)");
    // qry.prepare("select item_name, sales_price from inventory union select membership_number, item_name, quantity_purchased from sales where membership_number=(:membership_number)");

    qry.bindValue(":membership_number",membership_number);
    qry.exec();

    return qry;
}

