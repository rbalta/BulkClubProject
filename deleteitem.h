#ifndef DELETEITEM_H
#define DELETEITEM_H

#include <QDialog>

namespace Ui {
class deleteItem;
}

class deleteItem : public QDialog {
    Q_OBJECT

public:
    explicit deleteItem(QWidget *parent = nullptr);
    ~deleteItem();

private slots:
    void on_pushButton_clicked();

private:
    Ui::deleteItem *ui;
};

#endif // DELETEITEM_H
