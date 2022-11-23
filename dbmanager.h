#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>

class DbManager
{
public:
    DbManager(const QString& path);
    // LoginWindow functions
    bool passwordCheck();

    // Employee/MainWindow Functions

    // AdminWindow functions

    // ManagerWindow functions
    void displaySalesReport(int dayGiven);
    void displayTotalPurchases();
    void displayQuantity();
    void displayRebate();
    void displayMembership(int month);
    void displayItemQuant(QString itemName);
    void displayMemberPurchases(int memNum, QString memName);
private:
    QSqlDatabase main_db;
};

#endif // DBMANAGER_H
