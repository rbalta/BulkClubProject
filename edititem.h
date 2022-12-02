#ifndef EDITITEM_H
#define EDITITEM_H

#include <QDialog>

namespace Ui {
class editItem;
}

class editItem : public QDialog
{
    Q_OBJECT

public:
    explicit editItem(QWidget *parent = nullptr);
    ~editItem();

private slots:
    void on_pushButton_clicked();

private:
    Ui::editItem *ui;
};

#endif // EDITITEM_H
