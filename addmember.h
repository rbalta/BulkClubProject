#ifndef ADDMEMBER_H
#define ADDMEMBER_H

#include <QDialog>

namespace Ui {
class addmember;
}

class addmember : public QDialog {
    Q_OBJECT

public:
    explicit addmember(QWidget *parent = nullptr);
    ~addmember();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addmember *ui;
};

#endif // ADDMEMBER_H
