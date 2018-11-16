#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlTableModel>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    DataBase *db;
    QSqlTableModel *model;

private slots:
    // adapted from https://evileg.com/en/post/62/
    // Methods for Tableview
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();

};

#endif // MAINWINDOW_H
