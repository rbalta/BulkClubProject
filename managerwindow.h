#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QWidget>

namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = nullptr);
    ~ManagerWindow();
    //void displaySalesReport(dayGiven);
    //void displayTotalPurchases();
    //void displayQuantitiy();
    //void displayRebate();
    //void displayMembership(month);
    //void displayItemQuant(itemName);
    //void displayMemberPurchases(memNum, memName);

private slots:
    void on_pushButton_7_clicked();

private:
    Ui::ManagerWindow *ui;
};

#endif // MANAGERWINDOW_H
