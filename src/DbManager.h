/************************************************************
 * Example adapted from										*
 * https://katecpp.wordpress.com/2015/08/28/sqlite-with-qt/	*
 ************************************************************/

#ifndef DBMANGER_H
#define DBMANGER_H

#include <QString>
#include <QDate>
#include <QSqlDatabase>

class DbManager
{
public:
	//explicit DbManager();
    ~DbManager();
    DbManager(const QString path);

private:
    QSqlDatabase m_db;

public:
    bool addEntry(QString, QString, QDate, double, QString, QString);
    bool getEntry(QString, QString column="*", QString whereClause="WHERE StatementID > -10000");
    double updateSums(QString table, int posNeg);
};

#endif //DBMANGER_H