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
    void deleteItem(QString itemname);
    void editItemPrice(QString itemname, int price);
    void addItem(QString itemname, int price);
    void deleteMember(QString memberName, QString memberNum);
    void addMember(QString memberName, QString memberNum, QString type, QString expirationDate, QString totalSpent, QString rebateAmount);
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
