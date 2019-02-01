#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>

#include <QSqlDatabase>
#include <QTableView>
#include <QTabWidget> // QWidget to get both from above
#include <QDebug>
#include <QRegularExpression>

#include "DbManager.h"
#include "database.h"


/***********************
 * static declarations *
 ***********************/
DbManager *manager;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();

    //model with names if the columns
    this->createUI();
    ui->inputDate->setDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this);
    model2 = new QSqlTableModel(this);

    model->setTable(tableName);
    model2->setTable(tableName);

    model->setFilter("ammount > -0.01");
    model2->setFilter("ammount < 0");

    //Set column names
    for(int i=0, j=0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
        model2->setHeaderData(i,Qt::Horizontal,headers[j]);
    }

    //Sort ascending
    model->setSort(0,Qt::AscendingOrder);
    model2->setSort(0,Qt::AscendingOrder);
}

/*
creating UI */
void MainWindow::createUI()
{
    int numTabs = ui->tabWidget->count();
    QString tableNameChosen = "year2015";
    DbManager *manager;
    double sum = 0.00f;
    QRegExp sumComp("*sum");
    QRegExp plusComp("*plus");
    sumComp.setPatternSyntax(QRegExp::Wildcard);
    plusComp.setPatternSyntax(QRegExp::Wildcard);


    for(int i=1; i<numTabs; i++)
    {
        QWidget* tab = ui->tabWidget->widget(i);
        QList<QTableView *> tabItem= tab->findChildren<QTableView *>(QRegExp("year[1-9]Tab_view*"));
        QList<QLabel *> sumLabels = tab->findChildren<QLabel *>(QRegExp("year[1-9]_[sum,plus,minus]"));
        QString labeltext;

        if(sumLabels.count() == 3)
        {
            for (int k = 0; k<3; k++)
            {
                //sum-label
                if(sumComp.exactMatch(sumLabels[k]->objectName()))
                {
                    sum = sum + manager->updateSums(tableNameChosen, 0);
                    labeltext = QString::number(sum,'f',2);

                    if(sum>=0) sumLabels[k]->setStyleSheet("QLabel {color: green;}");
                    else sumLabels[k]->setStyleSheet("QLabel {color: red;}");
                }
                else if (plusComp.exactMatch(sumLabels[k]->objectName())) labeltext = QString::number(manager->updateSums(tableNameChosen, 10), 'f', 2);
                else labeltext = QString::number(manager->updateSums(tableNameChosen, -10), 'f', 2);

                //see https://www.color-hex.com/color/8e0000 for colors
                if(labeltext.toFloat()>=0) sumLabels[k]->setStyleSheet("QLabel {color: green;}");
                else sumLabels[k]->setStyleSheet("QLabel {color: red;}");

                labeltext = labeltext + " €";
                sumLabels[k]->setText(labeltext);

            }

            qDebug() << "numbers acquired";
        }
        else
        {
            qDebug() << "not enough fields for sums";
        }
        this->setupModel(tableNameChosen,
                    QStringList()   << trUtf8("statementID")
                                    << trUtf8("Date")
                                    << trUtf8("Ammount")
                                    << trUtf8("Payee")
                                    << trUtf8("Comment")
                        );

        if(tabItem.count() == 2)
        {
            tabItem[0]->setModel(model);
            tabItem[0]->setColumnHidden(0, true);                             // hiding id
            tabItem[0]->setSelectionBehavior(QAbstractItemView::SelectRows);  // Allow the selection of lines
            tabItem[0]->setSelectionMode(QAbstractItemView::SingleSelection); // maximum 1 row selected
            tabItem[0]->setEditTriggers(QAbstractItemView::NoEditTriggers);   // disable editing because of SQL fields
            tabItem[0]->horizontalHeader()->setStretchLastSection(true);

            tabItem[1]->setModel(model2);
            tabItem[1]->setColumnHidden(0, true);                             // hiding id
            tabItem[1]->setSelectionBehavior(QAbstractItemView::SelectRows);  // Allow the selection of lines
            tabItem[1]->setSelectionMode(QAbstractItemView::SingleSelection); // maximum 1 row selected
            tabItem[1]->setEditTriggers(QAbstractItemView::NoEditTriggers);   // disable editing because of SQL fields
            tabItem[1]->horizontalHeader()->setStretchLastSection(true);

            model->select(); // Fetches the data from the table
            model2->select(); // Fetches the data from the table

            tabItem[0]->resizeColumnsToContents();
            tabItem[1]->resizeColumnsToContents();
        }
        tableNameChosen = "year" + QString::number(2015+i);
    }
}

void MainWindow::updateUI(QWidget* currentTab)
{

    this->setupModel("year2015",
                        QStringList()   << trUtf8("statementID")
                                        << trUtf8("Date")
                                        << trUtf8("Ammount")
                                        << trUtf8("Payee")
                                        << trUtf8("Comment")
                    );
    this->createUI();
}

void MainWindow::on_pushInput_clicked()
{
    DbManager *manager = new DbManager("../data/adapted_DB2.db");
    int lfdID = 1;
    QDate date = ui->inputDate->date();                              // year for clustering and first value of ID
    int number = ui->inputAccNr->value();                           // account number if existing, otherwise used as thousand-seperator
    double ammount = ui->inputAmmount->value();                     // ammount = negative for payment, positive for income
    QString payee = ui->inputPayee->text();       // payee or payer, depending on income or payment
    QString comment = ui->inputComment->text();   // Comment field for additional information

    QString id = date.toString("yyyy") + "-" + QString("%1").arg(number, 3, 10, QChar('0')) +  "-" + QString("%1").arg(lfdID, 3, 10, QChar('0'));
    //QString lastID =
    manager->addEntry("year"+date.toString("yyyy"), id, date, ammount, payee, comment);
    std::cout << "You have inserted the following values" << std::endl;
    std::cout << "______________________________________" << std::endl;
    //std::cout << "Year: " << year << std::endl;
    std::cout << "Acc-Number: " << number << std::endl;
    std::cout << "Ammount: " << ammount << std::endl;
    qDebug() << "Payee: " << payee;
    qDebug() << "Comment: " << comment;
    std::cout << "______________________________________" << std::endl;
    qDebug() << "ID (if not exisiting): " << id;
    createUI();
    delete manager;

}
void MainWindow::on_action_add_single_Entry_triggered()
{
    QString table = "year2015";
    manager = new DbManager("../data/adapted_DB2.db");
    manager->getEntry(table);
    delete manager;
}

void MainWindow::currentDateUpdate()
{
    QDate newDate;
    ui->inputDate->setDate(newDate);
}
