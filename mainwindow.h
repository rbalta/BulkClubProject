#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTabSettings();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    bool on_pushButton_3_clicked(); // returns bool- true means member is exec

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
