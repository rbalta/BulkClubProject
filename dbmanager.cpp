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

// Login Window Functions
bool DbManager::idMatch(QString id)
{
    QSqlQuery idCheck;
    idCheck.prepare("SELECT * FROM users WHERE username = :id");
    idCheck.bindValue(":id", id);

    if (idCheck.exec() && idCheck.last())
        return true;
    else
        return false;
}

bool DbManager::passwordCheck(QString id, QString password)
{
    QSqlQuery passCheck;
    passCheck.prepare("SELECT password FROM users WHERE username = :id");
    passCheck.bindValue(":id", id);
    qDebug() << passCheck.value(0);

    if (passCheck.exec() && passCheck.last()
            && passCheck.value(0).toString() == password)
        return true;
    else
        return false;
}

QString DbManager::accessCheck(QString id)
{
    QSqlQuery privCheck;
    privCheck.prepare("SELECT access FROM users WHERE username = :id");
    privCheck.bindValue(":id", id);

    if (privCheck.exec() && privCheck.last())
        return privCheck.value(0).toString();
    else
        return "Error: No user access added.";
}


//MainWindow Functions
QSqlTableModel* DbManager::pullInventoryItems() // returns pointer for sql object that displays all items
{
        QSqlTableModel *items = new QSqlTableModel;

        items->setTable("inventory");
        items->select();
        items->setHeaderData(0, Qt::Horizontal, "Item");
        items->setHeaderData(1, Qt::Horizontal, "Price");
        items->setHeaderData(2, Qt::Horizontal, "Quantity");
        items->setHeaderData(3, Qt::Horizontal, "Category");

        return items;
}

bool DbManager::memberExists(int memNum)
{
    QSqlQuery memCheck;

    memCheck.prepare("SELECT * FROM members WHERE membership_number = :memNum");
    memCheck.bindValue(":memNum", memNum);

    if (memCheck.exec() && memCheck.next())
        return true;
    return false;
}

QSqlQuery DbManager::pullMemberInfo(int memNum)
{
    QSqlQuery memInfo;

    memInfo.prepare("SELECT * FROM members WHERE membership_number = :memNum");
    memInfo.bindValue(":memNum", memNum);
    memInfo.exec();

    return memInfo;
}

void DbManager::addTransaction(QDate date, int memNum, QStringList items, QList<int> quantities)
{
    QSqlQuery addTransaction;
    addTransaction.prepare("INSERT INTO sales (purchase_date, membership_number, item_name, quantity_purchased) "
    "VALUES (:date, :memNum, :item, :quantity)");

    for (int i = 0; i < items.size(); i++)
    {
    addTransaction.bindValue(":date", date);
    addTransaction.bindValue(":memNum", memNum);
    addTransaction.bindValue(":item", items.at(i));
    addTransaction.bindValue(":quantity", quantities.at(i));
    addTransaction.exec();
    }
}

void DbManager::addToMemberTotal(int memNum, const double price)
{
    QSqlQuery addToTotal;
    addToTotal.prepare("UPDATE members SET (total_spent = total_spent + :price) WHERE membership_number = :memNum");
    addToTotal.bindValue(":price", price);
    addToTotal.bindValue(":memNum", memNum);
    addToTotal.exec();
}

void DbManager::addToExecCashback(int memNum, const double totalBeforeTax, const double cashbackPercent)
{
    double cashback = totalBeforeTax * cashbackPercent;
    QSqlQuery addCashback;
    addCashback.prepare("UPDATE members SET (cashback = cashback + :cashback) WHERE membership_number = :memNum");
    addCashback.bindValue(":cashback", cashback);
    addCashback.bindValue(":memNum", memNum);
    addCashback.exec();
}
