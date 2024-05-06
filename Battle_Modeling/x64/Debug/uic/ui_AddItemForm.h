/********************************************************************************
** Form generated from reading UI file 'AddItemForm.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDITEMFORM_H
#define UI_ADDITEMFORM_H

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

class Ui_AddItemFormClass
{
public:
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_4;
    QPushButton *AddPowerCoef;
    QLabel *label_4;
    QLineEdit *changeViability;
    QPushButton *ToMenu;
    QLineEdit *ItemNameLineEdit;
    QPushButton *AddItemButton;
    QLineEdit *ItemPower;
    QListWidget *UnitTypes;
    QListWidget *ItemsListWidget;
    QLabel *label_5;
    QLabel *label_1;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_6;
    QLineEdit *PowerCoef;
    QPushButton *DeleteItemButton;

    void setupUi(QDialog *AddItemFormClass)
    {
        if (AddItemFormClass->objectName().isEmpty())
            AddItemFormClass->setObjectName("AddItemFormClass");
        AddItemFormClass->resize(843, 418);
        layoutWidget_2 = new QWidget(AddItemFormClass);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(0, 0, 841, 411));
        gridLayout_4 = new QGridLayout(layoutWidget_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        AddPowerCoef = new QPushButton(layoutWidget_2);
        AddPowerCoef->setObjectName("AddPowerCoef");

        gridLayout_4->addWidget(AddPowerCoef, 9, 5, 1, 1);

        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName("label_4");

        gridLayout_4->addWidget(label_4, 5, 3, 1, 2);

        changeViability = new QLineEdit(layoutWidget_2);
        changeViability->setObjectName("changeViability");

        gridLayout_4->addWidget(changeViability, 6, 3, 1, 2);

        ToMenu = new QPushButton(layoutWidget_2);
        ToMenu->setObjectName("ToMenu");
        ToMenu->setStyleSheet(QString::fromUtf8("background-color:#F0FFFF;\n"
"font-weight:800;\n"
"color:black;\n"
""));

        gridLayout_4->addWidget(ToMenu, 3, 5, 1, 1);

        ItemNameLineEdit = new QLineEdit(layoutWidget_2);
        ItemNameLineEdit->setObjectName("ItemNameLineEdit");

        gridLayout_4->addWidget(ItemNameLineEdit, 2, 3, 1, 2);

        AddItemButton = new QPushButton(layoutWidget_2);
        AddItemButton->setObjectName("AddItemButton");

        gridLayout_4->addWidget(AddItemButton, 5, 5, 1, 1);

        ItemPower = new QLineEdit(layoutWidget_2);
        ItemPower->setObjectName("ItemPower");

        gridLayout_4->addWidget(ItemPower, 4, 3, 1, 2);

        UnitTypes = new QListWidget(layoutWidget_2);
        UnitTypes->setObjectName("UnitTypes");

        gridLayout_4->addWidget(UnitTypes, 9, 3, 1, 1);

        ItemsListWidget = new QListWidget(layoutWidget_2);
        ItemsListWidget->setObjectName("ItemsListWidget");

        gridLayout_4->addWidget(ItemsListWidget, 1, 0, 11, 2);

        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName("label_5");

        gridLayout_4->addWidget(label_5, 7, 3, 1, 1);

        label_1 = new QLabel(layoutWidget_2);
        label_1->setObjectName("label_1");

        gridLayout_4->addWidget(label_1, 0, 0, 1, 2, Qt::AlignmentFlag::AlignHCenter);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName("label_3");

        gridLayout_4->addWidget(label_3, 3, 3, 1, 2);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName("label_2");

        gridLayout_4->addWidget(label_2, 1, 3, 1, 2);

        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName("label_6");

        gridLayout_4->addWidget(label_6, 7, 4, 1, 1);

        PowerCoef = new QLineEdit(layoutWidget_2);
        PowerCoef->setObjectName("PowerCoef");

        gridLayout_4->addWidget(PowerCoef, 9, 4, 1, 1);

        DeleteItemButton = new QPushButton(layoutWidget_2);
        DeleteItemButton->setObjectName("DeleteItemButton");

        gridLayout_4->addWidget(DeleteItemButton, 7, 5, 1, 1);


        retranslateUi(AddItemFormClass);

        QMetaObject::connectSlotsByName(AddItemFormClass);
    } // setupUi

    void retranslateUi(QDialog *AddItemFormClass)
    {
        AddItemFormClass->setWindowTitle(QCoreApplication::translate("AddItemFormClass", "AddItemForm", nullptr));
        AddPowerCoef->setText(QCoreApplication::translate("AddItemFormClass", "Add power coef", nullptr));
        label_4->setText(QCoreApplication::translate("AddItemFormClass", "Enter changes to unit health:", nullptr));
        changeViability->setText(QCoreApplication::translate("AddItemFormClass", "0", nullptr));
        ToMenu->setText(QCoreApplication::translate("AddItemFormClass", "Go back", nullptr));
        AddItemButton->setText(QCoreApplication::translate("AddItemFormClass", "Add Item", nullptr));
        ItemPower->setText(QCoreApplication::translate("AddItemFormClass", "0", nullptr));
        label_5->setText(QCoreApplication::translate("AddItemFormClass", "Choose type to change:", nullptr));
        label_1->setText(QCoreApplication::translate("AddItemFormClass", "Items", nullptr));
        label_3->setText(QCoreApplication::translate("AddItemFormClass", "Enter changes to base power:", nullptr));
        label_2->setText(QCoreApplication::translate("AddItemFormClass", "Enter item name:<b style =\"color:red;\">*</b>", nullptr));
        label_6->setText(QCoreApplication::translate("AddItemFormClass", "Enter power coef:", nullptr));
        PowerCoef->setText(QCoreApplication::translate("AddItemFormClass", "1", nullptr));
        DeleteItemButton->setText(QCoreApplication::translate("AddItemFormClass", "Delete Item", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddItemFormClass: public Ui_AddItemFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITEMFORM_H
