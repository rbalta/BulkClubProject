#include "addmember.h"
#include "ui_addmember.h"
#include "dbmanager.h"

addmember::addmember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addmember)
{
    ui->setupUi(this);
}

addmember::~addmember()
{
    delete ui;
}

void addmember::on_pushButton_clicked()
{
    DbManager db("C:\\Users\\Kelsey\\BulkClubProject\\bulkclubdb.db");
    QString item_name, sales_price;
    item_name= ui->textItemName->text();
    sales_price = ui->textItemPrice->text();
    db.addItem(item_name,sales_price);

}

