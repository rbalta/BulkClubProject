#include "changemember.h"
#include "ui_changemember.h"
#include "dbmanager.h"

changemember::changemember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changemember)
{
    ui->setupUi(this);
}

changemember::~changemember()
{
    delete ui;
}

void changemember::on_pushButton_clicked()
{
    DbManager db("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");
    QString membership_number, membership_type;
    membership_number= ui->lineEdit->text();
    membership_type = ui->lineEdit_2->text();
    db.changeMembership(membership_number,membership_type);
}

