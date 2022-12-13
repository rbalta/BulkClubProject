#include "deleteitem.h"
#include "ui_deleteitem.h"
#include "dbmanager.h"

deleteItem::deleteItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteItem)
{
    ui->setupUi(this);
}

deleteItem::~deleteItem()
{
    delete ui;
}

void deleteItem::on_pushButton_clicked()
{
    DbManager db("C:/Users/13109/Desktop/database/bulkclubdb.db");
    QString item_name;
    item_name= ui->deleteItemEdit->text();
    db.deleteItem(item_name);
}

