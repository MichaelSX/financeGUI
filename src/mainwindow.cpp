#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>

#include <QSqlDatabase>
#include <QTableView>
#include <QTabWidget> // QWidget to get both from above
#include <QDebug>
#include <QRegularExpression>
#include <QFile>
#include <QMessageBox>
//#include <QLineSeries>
#include <QtCharts>


#include "DbManager.h"

static QString databaseFile;



/***********************
 * static declarations *
 ***********************/
DbManager *manager;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    databaseFile = readConfigDirectory();
    //db = new DataBase();
    //db->connectToDataBase();

    //model with names if the columns
    this->createUI();
    ui->inputDate->setDate(QDate::currentDate());
    printCharts();
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
    DbManager *manager = new DbManager(databaseFile);
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

            //qDebug() << "numbers acquired";
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
                                    << trUtf8("SQLDate")
                        );

        if(tabItem.count() == 2)
        {
            tabItem[0]->setModel(model);
            tabItem[0]->setColumnHidden(0, true);                             // hiding id
            tabItem[0]->setSelectionBehavior(QAbstractItemView::SelectRows);  // Allow the selection of lines
            tabItem[0]->setSelectionMode(QAbstractItemView::SingleSelection); // maximum 1 row selected
            tabItem[0]->setEditTriggers(QAbstractItemView::NoEditTriggers);   // disable editing because of SQL fields
            tabItem[0]->horizontalHeader()->setStretchLastSection(true);
            tabItem[0]->setColumnHidden(5, true);

            tabItem[1]->setModel(model2);
            tabItem[1]->setColumnHidden(0, true);                             // hiding id
            tabItem[1]->setSelectionBehavior(QAbstractItemView::SelectRows);  // Allow the selection of lines
            tabItem[1]->setSelectionMode(QAbstractItemView::SingleSelection); // maximum 1 row selected
            tabItem[1]->setEditTriggers(QAbstractItemView::NoEditTriggers);   // disable editing because of SQL fields
            tabItem[1]->horizontalHeader()->setStretchLastSection(true);
            tabItem[1]->setColumnHidden(5, true);

            model->select(); // Fetches the data from the table
            model2->select(); // Fetches the data from the table

            tabItem[0]->resizeColumnsToContents();
            tabItem[1]->resizeColumnsToContents();
        }
        tableNameChosen = "year" + QString::number(2015+i);
    }
    delete manager;
}

void MainWindow::updateUI(QWidget* currentTab)
{

    this->setupModel("year2015",
                        QStringList()   << trUtf8("statementID")
                                        << trUtf8("Date")
                                        << trUtf8("Ammount")
                                        << trUtf8("Payee")
                                        << trUtf8("Comment")
                                        << trUtf8("SQLDate")
                    );
    this->createUI();
}

void MainWindow::on_pushInput_clicked()
{
    DbManager *manager = new DbManager(databaseFile);
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
    manager = new DbManager(databaseFile);
    manager->getEntry(table);
    delete manager;
}

void MainWindow::currentDateUpdate()
{
    QDate newDate;
    ui->inputDate->setDate(newDate);
}

void MainWindow::on_showButton_clicked()
{
  int numTabs = ui->tabWidget->count();
  QString begin = ui->dateEdit->date().toString(Qt::ISODate);
  QString end = ui->dateEdit_2->date().toString(Qt::ISODate);
  QString tableName = "year2015";
  QString prevFilter = "ammount > -0.01";
  QString prevFilter2="ammount < 0";

//  qDebug() << begin << " until " << end

  for(int i=1; i<numTabs; i++)
  {
    QWidget* currTab = ui->tabWidget->widget(i);
    qDebug() << i << "/" << numTabs-1;
    QList<QTableView *> tabItem= currTab->findChildren<QTableView *>(QRegExp("year[1-9]Tab_view*"));

    this->setupModel(tableName,
                QStringList()   << trUtf8("statementID")
                                << trUtf8("Date")
                                << trUtf8("Ammount")
                                << trUtf8("Payee")
                                << trUtf8("Comment")
                                << trUtf8("SQLDate")
                    );

    model->setFilter(prevFilter + " AND SQLDate >'" + begin  +"' AND SQLDate<'" +end+"'");
    model2->setFilter(prevFilter2 + " AND SQLDate >'" + begin + "' AND SQLDate<'" +end+"'");

    model->select(); // Fetches the data from the table
    model2->select(); // Fetches the data from the table

    tabItem[0]->setModel(model);
    tabItem[1]->setModel(model2);

    tableName = "year" + QString::number(2015+i);
  }
  printCharts();
}

QString MainWindow::readConfigDirectory()
{
  QFile defaultFile("../data/default_config.txt");
  QFile customFile("../data/config.txt");
  QString line;

  if(!customFile.open(QIODevice::ReadOnly))
  {
    if(!defaultFile.open(QIODevice::ReadOnly))
    {
      QMessageBox::information(0, "error", defaultFile.errorString());
    }
    else
    {
      QTextStream input(&defaultFile);

      while(!input.atEnd())
      {
        line = input.readLine();
      }
      customFile.close();
    }
  }
  else
  {
    QTextStream input(&customFile);
    while(!input.atEnd())
    {
      line = input.readLine();
    }
    customFile.close();
  }
  //QMessageBox::information(0, "Path", line);
  return line;
}

void MainWindow::printCharts()
{
  DbManager *manager = new DbManager(databaseFile);

  QtCharts::QLineSeries *monthlySaldo = new QtCharts::QLineSeries();
  QtCharts::QLineSeries *monthlySum   = new QtCharts::QLineSeries();
  QtCharts::QPieSeries  *categoryPie  = new QtCharts::QPieSeries();

  QChart *saldoChart  = new QChart();
  QChart *sumChart    = new QChart();
  QChart *pieChart    = new QChart();

  QDate currDate = QDate(2015,1,1);
  QDateTime *currentDateTime = new QDateTime(); // int year, month, day format
  double currentSaldo = 0.00f;
  double currentSum   = 0.00f;
  QPointF currPointSaldo;
  QPointF currPointSum;
  std::string categories[] = {"Tester2", "Tester", "Tester2", "Tester2", "Tester"};
  int sum=0;


  //add saldo and total data to each month from first to last year
  for(int year = 2015; year <= 2019; year++) // adapt to varaible year, depending on tables
  {
    for(int month=1;month<=12; month++)
    {
      currDate.setDate(year, month,1);
      currentDateTime->setDate(currDate);
      currentSaldo = manager->saldoMonth(year,month);
      currentSum = sum+manager->sumMonth(year,month);
      currPointSaldo.setX(currentDateTime->toMSecsSinceEpoch());
      currPointSaldo.setY(currentSaldo);
      currPointSum.setX(currentDateTime->toMSecsSinceEpoch());
      currPointSum.setY(currentSum);
      //qDebug() << "y = " << currentSaldo << " | x = " << currentDateTime->toMSecsSinceEpoch();
      monthlySaldo->append(currPointSaldo);
      monthlySum->append(currPointSum);
    }
    sum = sum+manager->sumMonth(year,12);
  }
  for(int k = 0; k < manager->getCategory(2015, 2016).size(); k++)
  {
    categoryPie->append(manager->getCategory(2015, 2016)[k].first,manager->ammountPerCategory(manager->getCategory(2015, 2016)[k].first, 2015, 2017));
  }


  saldoChart->legend()->hide();
  saldoChart->addSeries(monthlySaldo);
  saldoChart->setTitle("Saldo");
  sumChart->legend()->hide();
  sumChart->addSeries(monthlySum);
  sumChart->setTitle("Total");
  pieChart->addSeries(categoryPie);
  //pieChart->setTitle("Pie");

  QDateTimeAxis *axisX = new QDateTimeAxis;
  QDateTimeAxis *axisX2= new QDateTimeAxis;
  QValueAxis *axisY = new QValueAxis;
  QValueAxis *axisY2= new QValueAxis;

  //axisX->setTickCount(12*4/4-1);//every half Year
  axisX->setFormat("MM yy");
  axisX->setTitleText("Date");
  axisY->setLabelFormat("EUR %i"); // EUR %.2f for 2 decimal places
  //axisY->setTitleText("Ammount");
  axisY->setTickCount(9);
  axisY->setRange(-3000, 5000);

  axisX2->setFormat("MM yy");
  axisX2->setTitleText("Date");
  axisY2->setLabelFormat("EUR %i"); // EUR %.2f for 2 decimal places
  //axisY2->setTitleText("Ammount");
  axisY2->setTickCount(7);
  axisY2->setRange(0, 6000);

  saldoChart->addAxis(axisX, Qt::AlignBottom);
  sumChart->addAxis(axisX2, Qt::AlignBottom);
  monthlySaldo->attachAxis(axisX);
  monthlySum->attachAxis(axisX2);
  saldoChart->addAxis(axisY, Qt::AlignLeft);
  monthlySaldo->attachAxis(axisY);
  sumChart->addAxis(axisY2, Qt::AlignLeft);
  monthlySum->attachAxis(axisY2);


  ui->saldoLines->setChart(saldoChart);
  ui->totalLines->setChart(sumChart);
  ui->pieOverview->setChart(pieChart);

  //qDebug() << manager->getCategory(2015, 2016)[0].first; //First row, first element
  //qDebug() << manager->getCategory(2015, 2016)[1].second;
  delete manager;
}
