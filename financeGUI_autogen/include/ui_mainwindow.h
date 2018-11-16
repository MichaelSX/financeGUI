/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionOpen_Dataset;
    QAction *actionSave_Dataset;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *inputYear;
    QSpinBox *inputAccNr;
    QDoubleSpinBox *inputAmmount;
    QLineEdit *inputPayee;
    QLineEdit *inputComment;
    QPushButton *pushInput;
    QTabWidget *tabWidget;
    QWidget *overviewTab;
    QGridLayout *gridLayout_2;
    QGraphicsView *payeesDounut;
    QGraphicsView *SaldoLines;
    QScrollBar *horizontalScrollBar;
    QScrollBar *horizontalScrollBar_2;
    QGraphicsView *overallMoneyLines;
    QWidget *year1Tab;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QDateEdit *startDate1;
    QLabel *label_7;
    QDateEdit *endDate1;
    QPushButton *periodButton1;
    QSpacerItem *verticalSpacer;
    QTableView *tableView;
    QTableView *tableView_2;
    QWidget *year2Tab;
    QWidget *year3Tab;
    QWidget *year4Tab;
    QWidget *year5Tab;
    QMenuBar *menuBar;
    QMenu *menuFiles;
    QMenu *menuImport;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(704, 450);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionOpen->setEnabled(false);
        actionOpen_Dataset = new QAction(MainWindow);
        actionOpen_Dataset->setObjectName(QStringLiteral("actionOpen_Dataset"));
        actionOpen_Dataset->setEnabled(false);
        actionSave_Dataset = new QAction(MainWindow);
        actionSave_Dataset->setObjectName(QStringLiteral("actionSave_Dataset"));
        actionSave_Dataset->setEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 3, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 4, 1, 1);

        inputYear = new QSpinBox(centralWidget);
        inputYear->setObjectName(QStringLiteral("inputYear"));
        inputYear->setMinimum(1990);
        inputYear->setMaximum(2150);
        inputYear->setValue(2015);

        gridLayout->addWidget(inputYear, 1, 0, 1, 1);

        inputAccNr = new QSpinBox(centralWidget);
        inputAccNr->setObjectName(QStringLiteral("inputAccNr"));
        inputAccNr->setMinimum(1);
        inputAccNr->setMaximum(999);
        inputAccNr->setValue(1);

        gridLayout->addWidget(inputAccNr, 1, 1, 1, 1);

        inputAmmount = new QDoubleSpinBox(centralWidget);
        inputAmmount->setObjectName(QStringLiteral("inputAmmount"));
        inputAmmount->setMinimum(-9999);
        inputAmmount->setMaximum(9999);

        gridLayout->addWidget(inputAmmount, 1, 2, 1, 1);

        inputPayee = new QLineEdit(centralWidget);
        inputPayee->setObjectName(QStringLiteral("inputPayee"));

        gridLayout->addWidget(inputPayee, 1, 3, 1, 1);

        inputComment = new QLineEdit(centralWidget);
        inputComment->setObjectName(QStringLiteral("inputComment"));

        gridLayout->addWidget(inputComment, 1, 4, 1, 1);

        pushInput = new QPushButton(centralWidget);
        pushInput->setObjectName(QStringLiteral("pushInput"));

        gridLayout->addWidget(pushInput, 1, 5, 1, 1);


        verticalLayout->addLayout(gridLayout);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        overviewTab = new QWidget();
        overviewTab->setObjectName(QStringLiteral("overviewTab"));
        gridLayout_2 = new QGridLayout(overviewTab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        payeesDounut = new QGraphicsView(overviewTab);
        payeesDounut->setObjectName(QStringLiteral("payeesDounut"));

        gridLayout_2->addWidget(payeesDounut, 0, 0, 1, 1);

        SaldoLines = new QGraphicsView(overviewTab);
        SaldoLines->setObjectName(QStringLiteral("SaldoLines"));

        gridLayout_2->addWidget(SaldoLines, 0, 2, 1, 1);

        horizontalScrollBar = new QScrollBar(overviewTab);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalScrollBar, 1, 1, 1, 1);

        horizontalScrollBar_2 = new QScrollBar(overviewTab);
        horizontalScrollBar_2->setObjectName(QStringLiteral("horizontalScrollBar_2"));
        horizontalScrollBar_2->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalScrollBar_2, 1, 2, 1, 1);

        overallMoneyLines = new QGraphicsView(overviewTab);
        overallMoneyLines->setObjectName(QStringLiteral("overallMoneyLines"));

        gridLayout_2->addWidget(overallMoneyLines, 0, 1, 1, 1);

        tabWidget->addTab(overviewTab, QString());
        year1Tab = new QWidget();
        year1Tab->setObjectName(QStringLiteral("year1Tab"));
        horizontalLayout_2 = new QHBoxLayout(year1Tab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_6 = new QLabel(year1Tab);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_2->addWidget(label_6);

        startDate1 = new QDateEdit(year1Tab);
        startDate1->setObjectName(QStringLiteral("startDate1"));

        verticalLayout_2->addWidget(startDate1);

        label_7 = new QLabel(year1Tab);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_2->addWidget(label_7);

        endDate1 = new QDateEdit(year1Tab);
        endDate1->setObjectName(QStringLiteral("endDate1"));

        verticalLayout_2->addWidget(endDate1);

        periodButton1 = new QPushButton(year1Tab);
        periodButton1->setObjectName(QStringLiteral("periodButton1"));

        verticalLayout_2->addWidget(periodButton1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_2);

        tableView = new QTableView(year1Tab);
        tableView->setObjectName(QStringLiteral("tableView"));

        horizontalLayout_2->addWidget(tableView);

        tableView_2 = new QTableView(year1Tab);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));

        horizontalLayout_2->addWidget(tableView_2);

        tabWidget->addTab(year1Tab, QString());
        year2Tab = new QWidget();
        year2Tab->setObjectName(QStringLiteral("year2Tab"));
        year2Tab->setEnabled(false);
        tabWidget->addTab(year2Tab, QString());
        year3Tab = new QWidget();
        year3Tab->setObjectName(QStringLiteral("year3Tab"));
        year3Tab->setEnabled(false);
        tabWidget->addTab(year3Tab, QString());
        year4Tab = new QWidget();
        year4Tab->setObjectName(QStringLiteral("year4Tab"));
        year4Tab->setEnabled(false);
        tabWidget->addTab(year4Tab, QString());
        year5Tab = new QWidget();
        year5Tab->setObjectName(QStringLiteral("year5Tab"));
        year5Tab->setEnabled(false);
        tabWidget->addTab(year5Tab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 704, 24));
        menuFiles = new QMenu(menuBar);
        menuFiles->setObjectName(QStringLiteral("menuFiles"));
        menuFiles->setEnabled(false);
        menuImport = new QMenu(menuBar);
        menuImport->setObjectName(QStringLiteral("menuImport"));
        menuImport->setEnabled(false);
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuHelp->setEnabled(false);
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFiles->menuAction());
        menuBar->addAction(menuImport->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFiles->addAction(actionOpen);
        menuFiles->addAction(actionOpen_Dataset);
        menuFiles->addAction(actionSave_Dataset);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "New Dataset", nullptr));
        actionOpen_Dataset->setText(QApplication::translate("MainWindow", "Open Dataset", nullptr));
        actionSave_Dataset->setText(QApplication::translate("MainWindow", "Save Dataset", nullptr));
        label->setText(QApplication::translate("MainWindow", "Year", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Acc-Nr.", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Ammount", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Payee", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Comment", nullptr));
        inputYear->setSuffix(QString());
        inputAmmount->setSuffix(QApplication::translate("MainWindow", "\342\202\254", nullptr));
        pushInput->setText(QApplication::translate("MainWindow", "Insert", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(overviewTab), QApplication::translate("MainWindow", "overview", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Start Period", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "End Period", nullptr));
        periodButton1->setText(QApplication::translate("MainWindow", "Show", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(year1Tab), QApplication::translate("MainWindow", "2015", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(year2Tab), QApplication::translate("MainWindow", "2016", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(year3Tab), QApplication::translate("MainWindow", "2017", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(year4Tab), QApplication::translate("MainWindow", "2018", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(year5Tab), QApplication::translate("MainWindow", "2019", nullptr));
        menuFiles->setTitle(QApplication::translate("MainWindow", "Files", nullptr));
        menuImport->setTitle(QApplication::translate("MainWindow", "Import", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
