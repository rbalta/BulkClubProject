#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>


namespace Ui {
class AdminWindow;
}

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_pushButton_4_clicked();


    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();


    void on_pushButton_6_clicked();


    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
