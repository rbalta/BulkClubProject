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

//MainWindow Functions
void DbManager::pullInventoryItems()
{
    QSqlTableModel items;

    items.setTable("inventory");
    items.select();

    for (int i = 0; i < items.rowCount(); i++)
    {
        QSqlRecord invItem = items.record(i);
        QString name = invItem.value("item_name").toString();
        QString price = invItem.value("sales_price").toString();
        qDebug() << name << "  " << price;
    }
}

bool DbManager::memberExists(int memNum, bool& isExec)
{
    QSqlQuery memCheck;
    memCheck.prepare("SELECT * FROM members WHERE membership_number = (:memNum)");
    memCheck.bindValue(":memNum", memNum);
    bool success = memCheck.exec();
    qDebug() << memCheck; // work here
    if (success)
    {
        int id = memCheck.record().indexOf("memNum");
        QString name = memCheck.value(id).toString();
        qDebug() << name;
        if (memCheck.value("membership_type").toString() == "Executive")
            isExec = true;
        else
            isExec = false;
    }
    else
    {
        qDebug() << "Member error: " << memCheck.lastError();
    }
    return success;
}

//void DbManager::addTransaction(QDate date, int memNum, int item[], int quantity[])
//{

//}

//void DbManager::addToMemberTotal(int memNum, double price)
//{

//}

//void DbManager::addToExecCashback(int memNum, double cashback)
//{

//}
