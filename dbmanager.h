#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>

class DbManager {
public:
    DbManager(const QString& path);

    // LoginWindow functions
    bool idMatch(QString id);
    bool passwordCheck(QString id, QString password);
    QString accessCheck(QString id);

    // Employee/MainWindow Functions
    QSqlTableModel* pullInventoryItems();
    bool memberExists(int memNum);
    QSqlQuery pullMemberInfo(int memNum);
    void addTransaction(QDate date, int memNum, QStringList items, QList<int> quantities);
    void addToMemberTotal(int memNum, const double price);
    void addToExecCashback(int memNum, const double totalBeforeTax, const double cashbackPercent);

    // AdminWindow functions
    void deleteItem(QString itemname);
    void editItemPrice(QString item_name, QString sales_price);
    void addItem(QString item_name, QString sales_price);
    void deleteMember(QString memberNum);
    void addMember(QString member_name, QString membership_number, QString membership_type, QString membership_expiration);

    // ManagerWindow functions
    QSqlQuery qryDailyReport(QString purchase_date);
    QString calcDailyReportRev(QString purchase_date);
    QString calcDailyReportExecutive(QString purchase_date);
    QSqlQuery qryMemberReport(QString membership_number);
    double calcTax();
//    void qryItemQuant(QString quantity_purchased);
//    void calcRebate();
//    void qryMembershipExp(QString membership_expiration);
//    void qryMemberPurchases(QString membership_number, QString membership_name);

private:
    QSqlDatabase main_db;
};

#endif // DBMANAGER_H
