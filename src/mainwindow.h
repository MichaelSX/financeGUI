#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlTableModel>
//#include "database.h"

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

    //DataBase *db;
    QSqlTableModel *model;
    QSqlTableModel *model2;

private slots:
    // adapted from https://evileg.com/en/post/62/
    // Methods for Tableview
    void setupModel(const QString &tableName, const QStringList &headers);
    void on_pushInput_clicked();
    void on_action_add_single_Entry_triggered();
    void createUI();
    void updateUI(QWidget* currentTab);
    void currentDateUpdate();
    void on_showButton_clicked();
};

#endif // MAINWINDOW_H
