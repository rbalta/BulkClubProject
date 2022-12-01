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
