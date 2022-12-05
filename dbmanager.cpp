#include "dbmanager.h"

DbManager::DbManager(const QString& path)
{
    main_db = QSqlDatabase::addDatabase("QSQLITE");
    main_db.setDatabaseName(path);

    if (!main_db.open())
        qDebug() << "Error: Database not found.";
    else
        qDebug() << "Database connected.";
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
