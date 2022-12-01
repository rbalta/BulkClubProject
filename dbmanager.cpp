#include "dbmanager.h"

DbManager::DbManager(const QString& path)
{
    main_db = QSqlDatabase::addDatabase("QSQLITE");
    main_db.setDatabaseName(path);

    if (!main_db.open())
        qDebug() << "Error: Database not found.";
    else
        qDebug() << "Database connected.";
}
