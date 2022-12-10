#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>
#include <QMessageBox>
#include <QStandardItem>
#include <QSqlQuery>
#include <QSqlQueryModel>

class DbManager
{
public:

    DbManager(const QString& path);
    ~DbManager();

    // LoginWindow functions
    bool idMatch(QString id);
    bool passwordCheck(QString id, QString password);
    QString accessCheck(QString id);

    // Employee/MainWindow Functions
    QSqlTableModel* pullInventoryItems();
    bool memberExists(int memNum);
    QSqlQuery pullMemberInfo(int memNum);
    QStandardItemModel* pullSelectedInventory(QStringList items);
    void addTransaction(QString date, int memNum, QStringList items, QList<int> quantities);
    void addToMemberTotal(int memNum, const double price);
    void addToExecCashback(int memNum, const double totalBeforeTax, const double cashbackPercent);


    // AdminWindow functions
    void deleteItem(QString itemname);
    void editItemPrice(QString item_name, QString sales_price);
    void addItem(QString item_name, QString sales_price);
    void deleteMember(QString memberNum);
    void addMember(QString member_name, QString membership_number, QString membership_type, QString membership_expiration);
    void changeMembership(QString membership_number, QString membership_type);
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
