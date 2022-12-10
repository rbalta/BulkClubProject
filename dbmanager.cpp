#include "dbmanager.h"

DbManager::DbManager(const QString& path)
{
    main_db = QSqlDatabase::addDatabase("QSQLITE");
    main_db.setDatabaseName(path);

    if (main_db.open())
        qDebug() << "Database connected.";
    else
        qDebug() << "Error: Database not found.";
}

DbManager::~DbManager()
{
    if (main_db.isOpen())
    {
        main_db.close();
    }
}

// AdminWindow functions
//admin functions
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
void DbManager::changeMembership(QString membership_number, QString membership_type)
{
    QSqlQuery qry;
    qry.prepare("update members set membership_type='"+membership_type+"' where membership_number='"+membership_number+"'");
    if (qry.exec())
    {
        QMessageBox msg;
        msg.setText("Membership Updated");
        msg.exec();
    }
    else
    {

        QMessageBox msg;
        msg.setText("Failed to Update Membership");
        msg.exec();
    }
}

// ManagerWindow functions

// A store manager should be able to display a sales report for any
// given day. It should include a list of items and quantities sold on that
// day as well names of the members who shopped that day.
QSqlQuery DbManager::qryDailyReport(QString purchase_date) {
    //set query
    QSqlQuery qry;

    //create, bind, and execute query
    qry.prepare("SELECT sales.purchase_date, members.member_name, sales.item_name, sales.quantity_purchased "
                "FROM sales INNER JOIN members ON sales.membership_number = members.membership_number "
                "WHERE sales.purchase_date = (:purchase_date)");

    qry.bindValue(":purchase_date",purchase_date);
    qry.exec();

    //return to manager window
    return qry;
}

// Display the total revenue (including tax) for the given day.
QString DbManager::calcDailyReportRev(QString purchase_date) {
    //set query
    QSqlQuery qry;

    qry.prepare("SELECT ROUND(SUM (((inventory.sales_price * 1.0775)) * sales.quantity_purchased), 2) "
                "FROM sales INNER JOIN inventory ON sales.item_name = inventory.item_name "
                "WHERE sales.purchase_date = (:purchase_date)");

    qry.bindValue(":purchase_date",purchase_date);
    qry.exec();
    qry.next();

    return qry.value(0).toString();
}

// It should also include number of unique Executive members and Regular
// members who shopped during the given day.
QString DbManager::calcDailyReportExecutive(QString purchase_date) {
    QSqlQuery qry;

    qry.prepare("SELECT COUNT (DISTINCT sales.membership_number) "
                "FROM sales inner join members on sales.membership_number = members.membership_number "
                "WHERE members.membership_type = :membership_type AND sales.purchase_date = :purchase_date");
    qry.bindValue(":purchase_date",purchase_date);
    qry.bindValue(":membership_type", "Executive");
    qry.exec();
    qry.next();

    return qry.value(0).toString();
}

QString DbManager::calcDailyReportRegular(QString purchase_date) {
    QSqlQuery qry;

    qry.prepare("SELECT COUNT (DISTINCT sales.membership_number) "
                "FROM sales inner join members on sales.membership_number = members.membership_number "
                "WHERE members.membership_type = :membership_type AND sales.purchase_date = :purchase_date");
    qry.bindValue(":purchase_date",purchase_date);
    qry.bindValue(":membership_type", "Regular");
    qry.exec();
    qry.next();

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
    QSqlQuery qry;

    qry.prepare("SELECT sales.membership_number, inventory.item_name, inventory.sales_price, sales.quantity_purchased, "
                "ROUND((inventory.sales_price * 1.0775 * sales.quantity_purchased), 2) AS 'total_purchased' "
                "FROM sales inner join inventory on sales.item_name = inventory.item_name "
                "WHERE sales.membership_number = :membership_number");
    qry.bindValue(":membership_number",membership_number);
    qry.exec();

    return qry;
}

QString DbManager::calcMemberReportRev(QString membership_number) {
    //set query
    QSqlQuery qry;

    qry.prepare("SELECT ROUND(SUM (inventory.sales_price * 1.0775 * sales.quantity_purchased), 2) "
                "FROM sales inner join inventory on sales.item_name = inventory.item_name "
                "WHERE sales.membership_number = :membership_number");
    qry.bindValue(":membership_number",membership_number);
    qry.exec();
    qry.next();

    qDebug() << qry.value(0).toString();

    return qry.value(0).toString();
}

// A store manager should be able to display the quantity of each item
// sold sorted by item name and the total revenue (without tax) for
// each item.
QSqlQuery DbManager::qryItemReport(QString item_name) {
    //set query
    QSqlQuery qry;

    qry.prepare("SELECT inventory.item_name, sales.quantity_purchased, inventory.sales_price, "
                "(sales.quantity_purchased * inventory.sales_price) AS 'total_price' "
                "FROM sales inner join inventory on sales.item_name = inventory.item_name "
                "WHERE sales.item_name = (:item_name)");

    qry.bindValue(":item_name",item_name);
    qry.exec();

    return qry;
}

// A store manager should be able to enter an item name and only
// display the quantity of that item sold as well as the total revenue
// (without tax) for the item.  No other items should be displayed.
QString DbManager::qryItemRevenue(QString item_name) {
    //set query
    QSqlQuery qry;

    qry.prepare("SELECT ROUND(SUM (sales.quantity_purchased * inventory.sales_price), 2) "
                "FROM sales inner join inventory on sales.item_name = inventory.item_name "
                "WHERE sales.item_name = (:item_name)");

    qry.bindValue(":item_name",item_name);
    qry.exec();
    qry.next();

    return qry.value(0).toString();
}

// A store manager should be able to display the rebate of all the
// Executive members sorted by membership number. Rebates are
// based on purchases before tax.
QSqlQuery DbManager::qryRebate() {
    //set query
    QSqlQuery qry;
    qry.prepare("SELECT member_name, membership_number, membership_type, ROUND(((total_spent + 120) * 0.02), 2) as Rebate "
                "FROM members "
                "WHERE members.membership_type = 'Executive' ");
    qry.exec();

    return qry;
}

// A store manager should be able to enter a month and obtain a
// display of all members whose memberships expire that month as
// well as the cost to renew their memberships.
QSqlQuery DbManager::qryMemberExp(QString membership_expiration) {
    //set query
    QSqlQuery qry;
    qry.prepare("select membership_expiration, member_name, membership_type, "
                "CASE WHEN membership_type = 'Regular' THEN '65' "
                "ELSE '120' "
                "END AS 'Cost of Renewal' "
                "from members "
                "where membership_expiration=(:membership_expiration)");

    qry.bindValue(":membership_expiration",membership_expiration);
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

void DbManager::addTransaction(QString date, int memNum, QStringList items, QList<int> quantities)
{
    QSqlQuery addTransaction;

    for (int i = 0; i < items.size(); i++)
    {
    addTransaction.prepare("INSERT INTO sales (purchase_date, membership_number, item_name, quantity_purchased) "
                           "VALUES (:date, :memNum, :item, :quantity)");
    addTransaction.bindValue(":date", date);
    addTransaction.bindValue(":memNum", memNum);
    addTransaction.bindValue(":item", items[i]);
    addTransaction.bindValue(":quantity", quantities[i]);
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

QStandardItemModel* DbManager::pullSelectedInventory(QStringList items)
{
    QSqlQuery pullItem;
    QString joinedItems = items.join("' , '");
    joinedItems.insert(0, "('");
    joinedItems.append("')");

    QStandardItemModel *model = new QStandardItemModel(0, 3);
    model->setHeaderData(0,Qt::Horizontal, "Item");
    model->setHeaderData(1,Qt::Horizontal, "Price");
    model->setHeaderData(2,Qt::Horizontal, "Quantity");

    pullItem.exec("SELECT item_name, sales_price, quantity FROM inventory WHERE item_name in "+joinedItems+";");

    QString item = "";
    QString price = 0;

    while (pullItem.next())
    {
        QList<QStandardItem*> newRow;
        item = pullItem.value(0).toString();

        QStandardItem *newColumn = new QStandardItem(item);
        newRow.append(newColumn);

        price = pullItem.value(1).toString();
        newColumn = new QStandardItem(price);
        newRow.append(newColumn);

        newColumn = new QStandardItem("1");
        newRow.append(newColumn);

        model->appendRow(newRow);
    }

    return model;
}
