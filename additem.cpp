#include "additem.h"
#include "ui_additem.h"
#include "dbmanager.h"

addItem::addItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addItem)
{
    ui->setupUi(this);
}

addItem::~addItem()
{
    delete ui;
}

void addItem::on_pushButton_clicked()
{
    DbManager db("C:/Users/bounc/Documents/GitHub/BulkClubProject/bulkclubdb.db");
    QString member_name, membership_number, membership_type, membership_expiration;
    member_name= ui->nameEdit->text();
    membership_number = ui->memberNumberEdit->text();
    membership_type = ui->typeEdit->text();
    membership_type = ui->expirationEdit->text();
    db.addMember(member_name, membership_number, membership_type, membership_expiration);
}

