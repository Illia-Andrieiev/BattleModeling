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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QListWidget *ArmiesListWidget;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QPushButton *StartButton;
    QPushButton *ChangeCircumstancesButton;
    QPushButton *ChangeReinfButton;
    QPushButton *AddItemButton;
    QPushButton *AddCircumstanceButton;
    QPushButton *AddUnitButton;
    QPushButton *AddArmyButton;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *Army1LineEdit;
    QLabel *label_3;
    QLineEdit *Army2LineEdit;
    QLabel *label_4;
    QLineEdit *AmountLineEdit;
    QLabel *label_6;
    QLineEdit *Army2WinTargetLineEdit;
    QLabel *label_5;
    QLineEdit *Army1WinTargetLineEdit;
    QLabel *label_7;
    QLineEdit *SaveArmiesStateLineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName("MainWindowClass");
        MainWindowClass->resize(772, 600);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName("centralWidget");
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(7, -1, 761, 541));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        ArmiesListWidget = new QListWidget(layoutWidget);
        ArmiesListWidget->setObjectName("ArmiesListWidget");

        gridLayout->addWidget(ArmiesListWidget, 1, 0, 18, 2);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 2, Qt::AlignmentFlag::AlignHCenter);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        StartButton = new QPushButton(layoutWidget);
        StartButton->setObjectName("StartButton");
        StartButton->setStyleSheet(QString::fromUtf8("background-color:#F0FFFF;\n"
"font-weight:800;\n"
"color:black;\n"
""));

        verticalLayout->addWidget(StartButton);

        ChangeCircumstancesButton = new QPushButton(layoutWidget);
        ChangeCircumstancesButton->setObjectName("ChangeCircumstancesButton");

        verticalLayout->addWidget(ChangeCircumstancesButton);

        ChangeReinfButton = new QPushButton(layoutWidget);
        ChangeReinfButton->setObjectName("ChangeReinfButton");

        verticalLayout->addWidget(ChangeReinfButton);

        AddItemButton = new QPushButton(layoutWidget);
        AddItemButton->setObjectName("AddItemButton");

        verticalLayout->addWidget(AddItemButton);

        AddCircumstanceButton = new QPushButton(layoutWidget);
        AddCircumstanceButton->setObjectName("AddCircumstanceButton");

        verticalLayout->addWidget(AddCircumstanceButton);

        AddUnitButton = new QPushButton(layoutWidget);
        AddUnitButton->setObjectName("AddUnitButton");

        verticalLayout->addWidget(AddUnitButton);

        AddArmyButton = new QPushButton(layoutWidget);
        AddArmyButton->setObjectName("AddArmyButton");

        verticalLayout->addWidget(AddArmyButton);


        gridLayout->addLayout(verticalLayout, 0, 4, 19, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        Army1LineEdit = new QLineEdit(layoutWidget);
        Army1LineEdit->setObjectName("Army1LineEdit");

        verticalLayout_2->addWidget(Army1LineEdit);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        Army2LineEdit = new QLineEdit(layoutWidget);
        Army2LineEdit->setObjectName("Army2LineEdit");

        verticalLayout_2->addWidget(Army2LineEdit);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        AmountLineEdit = new QLineEdit(layoutWidget);
        AmountLineEdit->setObjectName("AmountLineEdit");

        verticalLayout_2->addWidget(AmountLineEdit);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");

        verticalLayout_2->addWidget(label_6);

        Army2WinTargetLineEdit = new QLineEdit(layoutWidget);
        Army2WinTargetLineEdit->setObjectName("Army2WinTargetLineEdit");

        verticalLayout_2->addWidget(Army2WinTargetLineEdit);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        Army1WinTargetLineEdit = new QLineEdit(layoutWidget);
        Army1WinTargetLineEdit->setObjectName("Army1WinTargetLineEdit");

        verticalLayout_2->addWidget(Army1WinTargetLineEdit);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName("label_7");

        verticalLayout_2->addWidget(label_7);

        SaveArmiesStateLineEdit = new QLineEdit(layoutWidget);
        SaveArmiesStateLineEdit->setObjectName("SaveArmiesStateLineEdit");

        verticalLayout_2->addWidget(SaveArmiesStateLineEdit);


        gridLayout->addLayout(verticalLayout_2, 0, 3, 19, 1);

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
        label->setText(QCoreApplication::translate("MainWindowClass", "Armies", nullptr));
        StartButton->setText(QCoreApplication::translate("MainWindowClass", "Start Modeling", nullptr));
        ChangeCircumstancesButton->setText(QCoreApplication::translate("MainWindowClass", "Change circumstances", nullptr));
        ChangeReinfButton->setText(QCoreApplication::translate("MainWindowClass", "Change reinforcements", nullptr));
        AddItemButton->setText(QCoreApplication::translate("MainWindowClass", "Add Item", nullptr));
        AddCircumstanceButton->setText(QCoreApplication::translate("MainWindowClass", "Add circumstance", nullptr));
        AddUnitButton->setText(QCoreApplication::translate("MainWindowClass", "Add unit", nullptr));
        AddArmyButton->setText(QCoreApplication::translate("MainWindowClass", "Add army", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindowClass", "Enter army 1 name:<b style=\"color:red;\">*</b>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindowClass", "Enter army 2 name:<b style=\"color:red;\">*</b>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindowClass", "Enter amount of modelings:", nullptr));
        AmountLineEdit->setText(QCoreApplication::translate("MainWindowClass", "1", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindowClass", "Army 1 sum health to loose: ", nullptr));
        Army2WinTargetLineEdit->setText(QCoreApplication::translate("MainWindowClass", "0", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindowClass", "Army 2 sum health to loose: ", nullptr));
        Army1WinTargetLineEdit->setText(QCoreApplication::translate("MainWindowClass", "0", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindowClass", "Save armies state every entered round:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
