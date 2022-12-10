#include "deletemember.h"
#include "ui_deletemember.h"
#include "dbmanager.h"

deleteMember::deleteMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteMember)
{
    ui->setupUi(this);
}

deleteMember::~deleteMember()
{
    delete ui;
}

void deleteMember::on_pushButton_clicked()
{
    DbManager db("C:/Users/13109/Desktop/database/bulkclubdb.db");
    QString membership_number;
    membership_number= ui->deleteMemberEdit->text();
    db.deleteMember(membership_number);
}

