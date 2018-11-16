#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>

#include "database.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();

    //model with names if the columns
    this->setupModel(TABLE,
                        QStringList()   << trUtf8("statementID")
                                        << trUtf8("Date")
                                        << trUtf8("Ammount")
                                        << trUtf8("Payee")
                                        << trUtf8("Comment")
                    );
    this->createUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    //Set column names
    for(int i=0, j=0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }

    //Sort ascending
    model->setSort(0,Qt::AscendingOrder);
}

/*
creating UI */
void MainWindow::createUI()
{
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true); //hiding id
    //Allow the selection of lines
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    model->select(); // Fetches the data from the table
    ui->tableView->resizeColumnsToContents();
}
