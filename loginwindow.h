#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLineEdit>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void keyPressEvent(QKeyEvent* login);
    void closeEvent(QCloseEvent *event);

    void on_pushButton_2_clicked(bool checked);

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
