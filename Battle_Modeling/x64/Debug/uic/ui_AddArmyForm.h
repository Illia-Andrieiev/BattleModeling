/********************************************************************************
** Form generated from reading UI file 'AddArmyForm.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDARMYFORM_H
#define UI_ADDARMYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddArmyFormClass
{
public:
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_4;
    QLineEdit *ArmyNameLineEdit;
    QLabel *label_1;
    QLabel *label_3;
    QLabel *label_2;
    QTableWidget *ArmyUnitsTable;
    QListWidget *UnitsListWidget;
    QListWidget *ArmiesListWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *ToMenu;
    QPushButton *AddFortificationButton;
    QPushButton *DeleteFortificationButton;
    QPushButton *AddArmyButton;
    QPushButton *DeleteArmyButton;
    QPushButton *AddUnitButton;
    QPushButton *DeleteUnitButton;
    QLabel *label;
    QLabel *fortification;

    void setupUi(QDialog *AddArmyFormClass)
    {
        if (AddArmyFormClass->objectName().isEmpty())
            AddArmyFormClass->setObjectName("AddArmyFormClass");
        AddArmyFormClass->resize(936, 493);
        layoutWidget_2 = new QWidget(AddArmyFormClass);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(0, 0, 931, 491));
        gridLayout_4 = new QGridLayout(layoutWidget_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        ArmyNameLineEdit = new QLineEdit(layoutWidget_2);
        ArmyNameLineEdit->setObjectName("ArmyNameLineEdit");

        gridLayout_4->addWidget(ArmyNameLineEdit, 1, 5, 1, 1);

        label_1 = new QLabel(layoutWidget_2);
        label_1->setObjectName("label_1");

        gridLayout_4->addWidget(label_1, 0, 3, 1, 2, Qt::AlignmentFlag::AlignHCenter);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName("label_3");

        gridLayout_4->addWidget(label_3, 0, 5, 1, 1);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName("label_2");

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        ArmyUnitsTable = new QTableWidget(layoutWidget_2);
        if (ArmyUnitsTable->columnCount() < 2)
            ArmyUnitsTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        ArmyUnitsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        ArmyUnitsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        ArmyUnitsTable->setObjectName("ArmyUnitsTable");

        gridLayout_4->addWidget(ArmyUnitsTable, 2, 5, 7, 1);

        UnitsListWidget = new QListWidget(layoutWidget_2);
        UnitsListWidget->setObjectName("UnitsListWidget");

        gridLayout_4->addWidget(UnitsListWidget, 1, 3, 8, 2);

        ArmiesListWidget = new QListWidget(layoutWidget_2);
        ArmiesListWidget->setObjectName("ArmiesListWidget");

        gridLayout_4->addWidget(ArmiesListWidget, 1, 0, 8, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        ToMenu = new QPushButton(layoutWidget_2);
        ToMenu->setObjectName("ToMenu");
        ToMenu->setStyleSheet(QString::fromUtf8("background-color:#F0FFFF;\n"
"font-weight:800;\n"
"color:black;\n"
""));

        verticalLayout->addWidget(ToMenu);

        AddFortificationButton = new QPushButton(layoutWidget_2);
        AddFortificationButton->setObjectName("AddFortificationButton");

        verticalLayout->addWidget(AddFortificationButton);

        DeleteFortificationButton = new QPushButton(layoutWidget_2);
        DeleteFortificationButton->setObjectName("DeleteFortificationButton");

        verticalLayout->addWidget(DeleteFortificationButton);

        AddArmyButton = new QPushButton(layoutWidget_2);
        AddArmyButton->setObjectName("AddArmyButton");

        verticalLayout->addWidget(AddArmyButton);

        DeleteArmyButton = new QPushButton(layoutWidget_2);
        DeleteArmyButton->setObjectName("DeleteArmyButton");

        verticalLayout->addWidget(DeleteArmyButton);

        AddUnitButton = new QPushButton(layoutWidget_2);
        AddUnitButton->setObjectName("AddUnitButton");

        verticalLayout->addWidget(AddUnitButton);

        DeleteUnitButton = new QPushButton(layoutWidget_2);
        DeleteUnitButton->setObjectName("DeleteUnitButton");

        verticalLayout->addWidget(DeleteUnitButton);


        gridLayout_4->addLayout(verticalLayout, 0, 7, 9, 1);

        label = new QLabel(layoutWidget_2);
        label->setObjectName("label");

        gridLayout_4->addWidget(label, 3, 6, 1, 1);

        fortification = new QLabel(layoutWidget_2);
        fortification->setObjectName("fortification");

        gridLayout_4->addWidget(fortification, 4, 6, 1, 1);


        retranslateUi(AddArmyFormClass);

        QMetaObject::connectSlotsByName(AddArmyFormClass);
    } // setupUi

    void retranslateUi(QDialog *AddArmyFormClass)
    {
        AddArmyFormClass->setWindowTitle(QCoreApplication::translate("AddArmyFormClass", "AddArmyForm", nullptr));
        label_1->setText(QCoreApplication::translate("AddArmyFormClass", "Available units", nullptr));
        label_3->setText(QCoreApplication::translate("AddArmyFormClass", "Enter army name:<b style =\"color:red;\">*</b>", nullptr));
        label_2->setText(QCoreApplication::translate("AddArmyFormClass", "Armies", nullptr));
        QTableWidgetItem *___qtablewidgetitem = ArmyUnitsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AddArmyFormClass", "Units", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = ArmyUnitsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AddArmyFormClass", "Amount", nullptr));
        ToMenu->setText(QCoreApplication::translate("AddArmyFormClass", "Go back", nullptr));
        AddFortificationButton->setText(QCoreApplication::translate("AddArmyFormClass", "Add fortification", nullptr));
        DeleteFortificationButton->setText(QCoreApplication::translate("AddArmyFormClass", "Delete fortification", nullptr));
        AddArmyButton->setText(QCoreApplication::translate("AddArmyFormClass", "Add Army", nullptr));
        DeleteArmyButton->setText(QCoreApplication::translate("AddArmyFormClass", "Delete Army", nullptr));
        AddUnitButton->setText(QCoreApplication::translate("AddArmyFormClass", "Add unit", nullptr));
        DeleteUnitButton->setText(QCoreApplication::translate("AddArmyFormClass", "Delete unit", nullptr));
        label->setText(QCoreApplication::translate("AddArmyFormClass", "Army fortification:", nullptr));
        fortification->setText(QCoreApplication::translate("AddArmyFormClass", "default", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddArmyFormClass: public Ui_AddArmyFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDARMYFORM_H
