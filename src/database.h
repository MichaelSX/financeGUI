#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

/* Directive table names, fields, tables, and databases */
#define DATABASE_HOSTNAME   "Finanzen2015"
#define DATABASE_NAME       "adapted_DB.db"

#define TABLE                   "Finanzen"
#define TABLE_ID                "statementID"
#define TABLE_DATE              "Date"
#define TABLE_AMMOUNT           "Ammount"
#define TABLE_PAYEE             "Payee"
#define TABLE_COMMENT           "Comment"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Methods for direct work with the class to connect
     * to a database and insert records into the table
     * */
    void connectToDataBase();
    bool inserIntoTable(const QVariantList &data);

private:
    // The very object database, which will be work
    QSqlDatabase    db;

private:
    /* Internal methods for working with database
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
};

#endif // DATABASE_H
