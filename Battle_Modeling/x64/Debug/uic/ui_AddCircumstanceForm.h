/********************************************************************************
** Form generated from reading UI file 'AddCircumstanceForm.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCIRCUMSTANCEFORM_H
#define UI_ADDCIRCUMSTANCEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddCircumstanceFormClass
{
public:
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_4;
    QListWidget *UnitTypes;
    QLineEdit *CircumstanceNameLineEdit;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *AddCircumstanceButton;
    QPushButton *ToMenu;
    QPushButton *AddPowerCoef;
    QLabel *label_2;
    QListWidget *CircumstancesListWidget;
    QLabel *label_1;
    QLineEdit *PowerCoef;
    QPushButton *DeleteCircumstanceButton;

    void setupUi(QDialog *AddCircumstanceFormClass)
    {
        if (AddCircumstanceFormClass->objectName().isEmpty())
            AddCircumstanceFormClass->setObjectName("AddCircumstanceFormClass");
        AddCircumstanceFormClass->resize(863, 354);
        layoutWidget_2 = new QWidget(AddCircumstanceFormClass);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(0, 0, 861, 351));
        gridLayout_4 = new QGridLayout(layoutWidget_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        UnitTypes = new QListWidget(layoutWidget_2);
        UnitTypes->setObjectName("UnitTypes");

        gridLayout_4->addWidget(UnitTypes, 7, 3, 6, 1);

        CircumstanceNameLineEdit = new QLineEdit(layoutWidget_2);
        CircumstanceNameLineEdit->setObjectName("CircumstanceNameLineEdit");

        gridLayout_4->addWidget(CircumstanceNameLineEdit, 5, 3, 1, 2);

        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName("label_5");

        gridLayout_4->addWidget(label_5, 6, 3, 1, 1);

        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName("label_6");

        gridLayout_4->addWidget(label_6, 6, 4, 1, 1);

        AddCircumstanceButton = new QPushButton(layoutWidget_2);
        AddCircumstanceButton->setObjectName("AddCircumstanceButton");

        gridLayout_4->addWidget(AddCircumstanceButton, 6, 5, 1, 1);

        ToMenu = new QPushButton(layoutWidget_2);
        ToMenu->setObjectName("ToMenu");
        ToMenu->setStyleSheet(QString::fromUtf8("background-color:#F0FFFF;\n"
"font-weight:800;\n"
"color:black;\n"
""));

        gridLayout_4->addWidget(ToMenu, 5, 5, 1, 1);

        AddPowerCoef = new QPushButton(layoutWidget_2);
        AddPowerCoef->setObjectName("AddPowerCoef");

        gridLayout_4->addWidget(AddPowerCoef, 10, 5, 1, 1);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName("label_2");

        gridLayout_4->addWidget(label_2, 4, 3, 1, 1);

        CircumstancesListWidget = new QListWidget(layoutWidget_2);
        CircumstancesListWidget->setObjectName("CircumstancesListWidget");

        gridLayout_4->addWidget(CircumstancesListWidget, 5, 0, 8, 2);

        label_1 = new QLabel(layoutWidget_2);
        label_1->setObjectName("label_1");

        gridLayout_4->addWidget(label_1, 4, 0, 1, 2, Qt::AlignmentFlag::AlignHCenter);

        PowerCoef = new QLineEdit(layoutWidget_2);
        PowerCoef->setObjectName("PowerCoef");

        gridLayout_4->addWidget(PowerCoef, 10, 4, 1, 1);

        DeleteCircumstanceButton = new QPushButton(layoutWidget_2);
        DeleteCircumstanceButton->setObjectName("DeleteCircumstanceButton");

        gridLayout_4->addWidget(DeleteCircumstanceButton, 8, 5, 1, 1);


        retranslateUi(AddCircumstanceFormClass);

        QMetaObject::connectSlotsByName(AddCircumstanceFormClass);
    } // setupUi

    void retranslateUi(QDialog *AddCircumstanceFormClass)
    {
        AddCircumstanceFormClass->setWindowTitle(QCoreApplication::translate("AddCircumstanceFormClass", "AddCircumstanceForm", nullptr));
        label_5->setText(QCoreApplication::translate("AddCircumstanceFormClass", "Choose type to change:", nullptr));
        label_6->setText(QCoreApplication::translate("AddCircumstanceFormClass", "Enter power coef:", nullptr));
        AddCircumstanceButton->setText(QCoreApplication::translate("AddCircumstanceFormClass", "Add Circumstance", nullptr));
        ToMenu->setText(QCoreApplication::translate("AddCircumstanceFormClass", "Go back", nullptr));
        AddPowerCoef->setText(QCoreApplication::translate("AddCircumstanceFormClass", "Add power coef", nullptr));
        label_2->setText(QCoreApplication::translate("AddCircumstanceFormClass", "Enter circumstance name:<b style =\"color:red;\">*</b>", nullptr));
        label_1->setText(QCoreApplication::translate("AddCircumstanceFormClass", "Circumstances", nullptr));
        PowerCoef->setText(QCoreApplication::translate("AddCircumstanceFormClass", "1", nullptr));
        DeleteCircumstanceButton->setText(QCoreApplication::translate("AddCircumstanceFormClass", "Delete Circumstance", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddCircumstanceFormClass: public Ui_AddCircumstanceFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCIRCUMSTANCEFORM_H
