#ifndef CHANGEMEMBER_H
#define CHANGEMEMBER_H

#include <QDialog>

namespace Ui {
class changemember;
}

class changemember : public QDialog
{
    Q_OBJECT

public:
    explicit changemember(QWidget *parent = nullptr);
    ~changemember();

private slots:
    void on_pushButton_clicked();

private:
    Ui::changemember *ui;
};

#endif // CHANGEMEMBER_H
