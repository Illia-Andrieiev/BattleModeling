/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *Army2LineEdit;
    QLineEdit *Army2WiTargetLineEdit;
    QLabel *label_2;
    QLineEdit *Army1WinTargetLineEdit;
    QLabel *label_4;
    QLineEdit *AmountLineEdit;
    QLabel *label_3;
    QPushButton *AddItemButton;
    QLineEdit *SaveArmiesStateLineEdit;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_6;
    QPushButton *AddCircumstanceButton;
    QLineEdit *Army1LineEdit;
    QLabel *label;
    QPushButton *AddArmyButton;
    QPushButton *AddUnitButton;
    QListWidget *ArmiesListWidget;
    QPushButton *StartButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName("MainWindowClass");
        MainWindowClass->resize(772, 550);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName("centralWidget");
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(7, -1, 761, 491));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Army2LineEdit = new QLineEdit(layoutWidget);
        Army2LineEdit->setObjectName("Army2LineEdit");

        gridLayout->addWidget(Army2LineEdit, 4, 3, 1, 1);

        Army2WiTargetLineEdit = new QLineEdit(layoutWidget);
        Army2WiTargetLineEdit->setObjectName("Army2WiTargetLineEdit");

        gridLayout->addWidget(Army2WiTargetLineEdit, 10, 3, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 3, 1, 1);

        Army1WinTargetLineEdit = new QLineEdit(layoutWidget);
        Army1WinTargetLineEdit->setObjectName("Army1WinTargetLineEdit");

        gridLayout->addWidget(Army1WinTargetLineEdit, 8, 3, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 5, 3, 1, 1);

        AmountLineEdit = new QLineEdit(layoutWidget);
        AmountLineEdit->setObjectName("AmountLineEdit");

        gridLayout->addWidget(AmountLineEdit, 6, 3, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 3, 3, 1, 1);

        AddItemButton = new QPushButton(layoutWidget);
        AddItemButton->setObjectName("AddItemButton");

        gridLayout->addWidget(AddItemButton, 8, 4, 1, 1);

        SaveArmiesStateLineEdit = new QLineEdit(layoutWidget);
        SaveArmiesStateLineEdit->setObjectName("SaveArmiesStateLineEdit");

        gridLayout->addWidget(SaveArmiesStateLineEdit, 12, 3, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 7, 3, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 11, 3, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 9, 3, 1, 1);

        AddCircumstanceButton = new QPushButton(layoutWidget);
        AddCircumstanceButton->setObjectName("AddCircumstanceButton");

        gridLayout->addWidget(AddCircumstanceButton, 10, 4, 1, 1);

        Army1LineEdit = new QLineEdit(layoutWidget);
        Army1LineEdit->setObjectName("Army1LineEdit");

        gridLayout->addWidget(Army1LineEdit, 2, 3, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 2, Qt::AlignmentFlag::AlignHCenter);

        AddArmyButton = new QPushButton(layoutWidget);
        AddArmyButton->setObjectName("AddArmyButton");

        gridLayout->addWidget(AddArmyButton, 14, 4, 1, 1);

        AddUnitButton = new QPushButton(layoutWidget);
        AddUnitButton->setObjectName("AddUnitButton");

        gridLayout->addWidget(AddUnitButton, 12, 4, 1, 1);

        ArmiesListWidget = new QListWidget(layoutWidget);
        ArmiesListWidget->setObjectName("ArmiesListWidget");

        gridLayout->addWidget(ArmiesListWidget, 1, 0, 14, 2);

        StartButton = new QPushButton(layoutWidget);
        StartButton->setObjectName("StartButton");
        StartButton->setStyleSheet(QString::fromUtf8("background-color:#F0FFFF;\n"
"font-weight:800;\n"
"color:black;\n"
""));

        gridLayout->addWidget(StartButton, 6, 4, 1, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 772, 21));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName("mainToolBar");
        MainWindowClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName("statusBar");
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QCoreApplication::translate("MainWindowClass", "MainWindow", nullptr));
        Army2WiTargetLineEdit->setText(QCoreApplication::translate("MainWindowClass", "0", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindowClass", "Enter army 1 name:<b style=\"color:red;\">*</b>", nullptr));
        Army1WinTargetLineEdit->setText(QCoreApplication::translate("MainWindowClass", "0", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindowClass", "Enter amount of modelings:", nullptr));
        AmountLineEdit->setText(QCoreApplication::translate("MainWindowClass", "1", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindowClass", "Enter army 2 name:<b style=\"color:red;\">*</b>", nullptr));
        AddItemButton->setText(QCoreApplication::translate("MainWindowClass", "Add Item", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindowClass", "Army 1 foes units health to win: ", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindowClass", "Save armies state every entered round:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindowClass", "Army 2 foes units health to win: ", nullptr));
        AddCircumstanceButton->setText(QCoreApplication::translate("MainWindowClass", "Add circumstance", nullptr));
        label->setText(QCoreApplication::translate("MainWindowClass", "Armies", nullptr));
        AddArmyButton->setText(QCoreApplication::translate("MainWindowClass", "Add army", nullptr));
        AddUnitButton->setText(QCoreApplication::translate("MainWindowClass", "Add unit", nullptr));
        StartButton->setText(QCoreApplication::translate("MainWindowClass", "Start Modeling", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
