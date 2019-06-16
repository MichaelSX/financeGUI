import sqlite3
from datetime import datetime

#establish connection
dbname = input('Name/Path of db?: ')
tablename =input('Name of table?: ')
conn = sqlite3.connect(dbname)

#Cursor is required to execute SQL-commands
curs = conn.cursor()
curs2 = conn.cursor()

SQLQuery = "SELECT StatementID, Date, SQLDate from " + tablename + ";"
for row in curs.execute(SQLQuery):
    print(row)
    statement=str(row[0])
    date1=row[1]
    date2=str(datetime.strptime(date1, '%d.%m.%Y').strftime('%Y-%m-%dT%I:%M:%S'))
    #print(statement)
    #print(row)
    #print(date2)
    execution="UPDATE "+tablename+" SET SQLDate = '"+date2+"' WHERE StatementID = '"+statement+"';"
    #print(execution)
    curs2.execute(execution)
    print(row)
    conn.commit()

#close connection
conn.close()
