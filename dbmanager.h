#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>

class DbManager
{
public:

    DbManager(const QString& path);
    // LoginWindow functions
    bool idMatch(int id);
    bool passwordCheck(int id, QString* password);
    void privilegeCheck(int id);

    // Employee/MainWindow Functions
    void displayInventoryItems();
    void addTransaction(QDate date, int memNum, int item[], int quantity[]);
    void addToMemberTotal(int memNum, double price);
    void addToExecCashback(int memNum, double cashback);

    // AdminWindow functions
    void deleteItem(QString itemname);
    void editItemPrice(QString itemname, QString price);
    void addItem(QString item_name, QString sales_price);
    void deleteMember(QString memberName, QString memberNum);
    void addMember(QString member_name, QString membership_number, QString membership_type, QString membership_expiration);
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
