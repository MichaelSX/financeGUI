#include "database.h"
#include <iostream>
 
DataBase::DataBase(QObject *parent) : QObject(parent)
{
 
}
 
DataBase::~DataBase()
{
 
}
 
/* Methods for connecting to the database
 * */
void DataBase::connectToDataBase()
{
    /* Before connecting to a database checks for its existence. 
     * Depending on the result of the opening of manufacture database or its recovery
     * */
    if(!QFile("./data/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
        std::cout << "database  opened" << std::endl;
    }
}
 
/* Methods for restoring the database
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        std::cout << "database could be opened" << std::endl;
        if(!this->createTable()){
            std::cout << "table not created" << std::endl;
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Failed to restore the database";
        return false;
    }
    return false;
}
 
/* The method to open the database
 * */
bool DataBase::openDataBase()
{
    /* Database opens along a predetermined path and the database name, if it exists
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("./data/" DATABASE_NAME);
    if(db.open()){
        return true;

    } else {
        return false;
    }
}
 
/* Method for closing database
 * */
void DataBase::closeDataBase()
{
    db.close();
}
 
/* The method for creating a database table
 * */
bool DataBase::createTable()
{
    /* In this case, a forming raw SQL-query with its subsequent execution.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            TABLE_ID " VARCHAR(255) PRIMARY KEY, "
                            TABLE_DATE     " DATE            NOT NULL,"
                            TABLE_AMMOUNT      " FLOAT            NOT NULL,"
                            TABLE_PAYEE    " VARCHAR(255)         NOT NULL,"
                            TABLE_COMMENT   " VARCHAR(255)    NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
 
/* The method to insert records into the database
 * */
bool DataBase::inserIntoTable(const QVariantList &data)
{
    /* SQL Query formed from QVariantList, 
     * which are transmitted in data to be inserted into the table.
     * */
    QSqlQuery query;
    /* e SQL query is generated beginning with keys, 
     * which then bind with bindValue method for substituting data from QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_ID ", "
                                             TABLE_DATE ", "
                                             TABLE_AMMOUNT ", "
                                             TABLE_PAYEE ", "
                                             TABLE_COMMENT " ) "
                  "VALUES (:Id, :Date, :Ammount, :Payee, :Comment )");
    query.bindValue(":Id",        data[0].toString());
    query.bindValue(":Date",        data[1].toDate());
    query.bindValue(":Ammount",        data[2].toFloat());
    query.bindValue(":Payee",      data[3].toString());
    query.bindValue(":Comment",     data[4].toString());
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
