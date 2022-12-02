#include "edititem.h"
#include "ui_edititem.h"
#include "dbmanager.h"

editItem::editItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editItem)
{
    ui->setupUi(this);
}

editItem::~editItem()
{
    delete ui;
}

void editItem::on_pushButton_clicked()
{
    DbManager db("C:/Users/bounc/Documents/GitHub/BulkClubProject/bulkclubdb.db");
    QString item_name, sales_price;
    item_name= ui->updateNameEdit->text();
    sales_price = ui->UpdatePriceEdit->text();
    db.editItemPrice(item_name,sales_price);
}

