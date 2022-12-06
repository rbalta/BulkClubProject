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
    //qry.prepare("sum(quantity_purchased.sales*sales_price.inventory) as total_price.inventory from sales inner join inventory where purchase_date=(:purchase_date)");
    qry.prepare("select total_price from inventory where item_name=(:item_name)");
    qry.bindValue(":item_name",purchase_date);
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


    qry.prepare("select sales.membership_number, inventory.item_name, sales.quantity_purchased, sales.sales_price "
                "from inventory inner join sales on inventory.item_name=sales.item_name where membership_number=(:membership_number)");
    qry.bindValue(":membership_number",membership_number);
    qry.exec();

    return qry;
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
    addTransaction.prepare("INSERT INTO sales VALUES "); // finish this

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
