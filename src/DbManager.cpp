/************************************************************
 * Example adapted from										*
 * https://katecpp.wordpress.com/2015/08/28/sqlite-with-qt/	*
 ************************************************************/
#include <iostream>
#include <sstream>
#include <string>
//#include <iostream>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QSqlError>

#include "DbManager.h"

DbManager::DbManager(const QString path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(path);

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database fail";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}

DbManager::~DbManager()
{

}


bool DbManager::addEntry(QString table, QString id, QDate current, double ammount, QString payee, QString comment)
{
   bool success = false;
   // you should check if args are ok first...
   QSqlQuery query2;
   QString queryString2 = "SELECT StatementID from " + table + " where StatementID LIKE \'" + id.mid(0,8) + "%\' ";
   qDebug() << queryString2;
   query2.prepare(queryString2);
   QString lastID = "0000-000-000";

   /*query2.prepare("SELECT StatementID from (:table) where StatementID LIKE (:id)%");
   query2.bindValue(":table", table);
   query2.bindValue(":id", id.mid(0,8));
   */

   if(query2.exec())
   {
   		while(query2.next())
   		{
   			qDebug() << query2.value(0);
   			if(lastID.mid(9,3).toInt() < query2.value(0).toString().mid(9,3).toInt()) lastID = query2.value(0).toString();
   		}

   		qDebug() << "lastID: " << lastID;
   		if (id <= lastID)
   		{
   			qDebug() << " new value = " << QString("%1").arg(lastID.mid(9,3).toInt()+1, 3, 10, QChar('0'));
   			id = id.mid(0,8) + "-" + QString("%1").arg(lastID.mid(9,3).toInt()+1, 3, 10, QChar('0'));
   		}
   		else
   		{
   			//id =
   		}
   }
   else
   {
   		qDebug() << "getID error:  " << query2.lastError();
   		return false;
   }



    query2.prepare("INSERT INTO "+ table + " (StatementID, Date, Ammount, Payee, Comment, SQLDate) "
                  "VALUES (:id, :date, :ammount, :payee, :comment, :sqldate)");
    query2.bindValue(":id", id);
    query2.bindValue(":date", current.toString("dd.MM.yyyy"));
    query2.bindValue(":ammount", ammount);
    query2.bindValue(":payee", payee);
    query2.bindValue(":comment", comment);
    query2.bindValue(":sqldate", current.toString("YYYY-MM-DD HH:MM:SS"));

   if(query2.exec())
   {
       success = true;
       qDebug() << "Values inserted";
   }
   else
   {
        qDebug() << "addEntry error:  " << query2.lastError();
   }

   return success;
}

bool DbManager::getEntry(QString table, QString column, QString whereClause)
{
   bool success = false;
   // you should check if args are ok first...
   QSqlQuery query;
   std::cout << "getentry executed with " << std::endl;
   std::cout << "table: " << table.toStdString() << std::endl;
   std::cout << "column: " << column.toStdString() << std::endl;
   std::cout << "where: " << whereClause.toStdString() << std::endl;
   std::cout << "Statement: SELECT " << column.toStdString() << " FROM " << table.toStdString() << " " << whereClause.toStdString() << std::endl;

   // workaround, as table names are to lng for binding values
   std::stringstream ss;
   ss << "SELECT " << column.toStdString() << " FROM " << table.toStdString() << " " << whereClause.toStdString() << ";";
   QString queryString = QString::fromStdString(ss.str());

   query.prepare(queryString);
   //query.bindValue(":column", column);
   //query.bindValue(":table1", "year");
   //query.bindValue(":table2", "2015");
   //query.bindValue(":where", "where StatementID > 0");

   if(query.exec())
   {
		while (query.next())
		{
        	std::cout << query.value(1).toString().toStdString() << " | " << query.value(2).toString().toStdString() << std::endl;
        	//qDebug() << name << salary;
        }
       success = true;
       //query.c_str();
   }
   else
   {
        qDebug() << "getEntry error:  " << query.lastError();
   }

   return success;
}
double DbManager::updateSums(QString table, int posNeg)
{
	double sum = 0.00f;
	QSqlQuery query;
	QString prepareStatement;
	if(posNeg > 0) prepareStatement = "SELECT Ammount from " + table + " where Ammount >-0.01";		// positive
	else if (posNeg < 0) prepareStatement = "SELECT Ammount from " + table + " where Ammount <0";	// negative
	else prepareStatement = "SELECT Ammount from " + table;											// all

	query.prepare(prepareStatement);
	   if(query.exec())
   {
		while (query.next())
		{
			sum = sum + query.value(0).toDouble();
			//qDebug() << query.value(0).toInt();
        }
    }
   else
   {
        qDebug() << "updateSum error:  " << query.lastError();
   }
   //std::cout << " The sum is " << sum << std::endl;
   return sum;
}
/*
if (personExists(name))
{
   QSqlQuery query;
   query.prepare("DELETE FROM people WHERE name = (:name)");
   query.bindValue(":name", name);
   success = query.exec();

   if(!success)
   {
       qDebug() << "removePerson error: "
                << query.lastError();
   }
}
*/
