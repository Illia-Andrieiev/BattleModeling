/********************************************************************************
** Form generated from reading UI file 'AddUnitForm.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDUNITFORM_H
#define UI_ADDUNITFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddUnitFormClass
{
public:
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_4;
    QLabel *label_5;
    QLabel *label_8;
    QListWidget *UnitsListWidget;
    QPushButton *ToMenu;
    QLabel *label_4;
    QLineEdit *UnitArmor;
    QLabel *label_2;
    QLineEdit *UnitMorality;
    QPushButton *ChangeItemsButton;
    QLabel *label_9;
    QLineEdit *UnitMoralityChanges;
    QListWidget *UnitTypes;
    QLabel *ChoosedUnitTargetType;
    QLabel *ChoosedUnitType;
    QLineEdit *changeViability;
    QListWidget *UnitTargetTypes;
    QLabel *label_3;
    QPushButton *DeleteUnitButton;
    QLabel *label_6;
    QLineEdit *UnitMaxPower;
    QLabel *label_7;
    QLabel *label_1;
    QLineEdit *UnitMinPower;
    QLineEdit *UnitNameLineEdit;
    QLabel *label_10;
    QPushButton *AddUnit;
    QCheckBox *fortificationTargetCheckBox;
    QCheckBox *renovareArmorCheckBox;

    void setupUi(QDialog *AddUnitFormClass)
    {
        if (AddUnitFormClass->objectName().isEmpty())
            AddUnitFormClass->setObjectName("AddUnitFormClass");
        AddUnitFormClass->resize(841, 523);
        layoutWidget_2 = new QWidget(AddUnitFormClass);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(0, 0, 841, 521));
        gridLayout_4 = new QGridLayout(layoutWidget_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName("label_5");

        gridLayout_4->addWidget(label_5, 14, 3, 1, 1);

        label_8 = new QLabel(layoutWidget_2);
        label_8->setObjectName("label_8");

        gridLayout_4->addWidget(label_8, 12, 3, 1, 1);

        UnitsListWidget = new QListWidget(layoutWidget_2);
        UnitsListWidget->setObjectName("UnitsListWidget");

        gridLayout_4->addWidget(UnitsListWidget, 1, 0, 18, 2);

        ToMenu = new QPushButton(layoutWidget_2);
        ToMenu->setObjectName("ToMenu");
        ToMenu->setStyleSheet(QString::fromUtf8("background-color:#F0FFFF;\n"
"font-weight:800;\n"
"color:black;\n"
""));

        gridLayout_4->addWidget(ToMenu, 2, 5, 1, 1);

        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName("label_4");

        gridLayout_4->addWidget(label_4, 8, 3, 1, 2);

        UnitArmor = new QLineEdit(layoutWidget_2);
        UnitArmor->setObjectName("UnitArmor");

        gridLayout_4->addWidget(UnitArmor, 11, 3, 1, 1);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName("label_2");

        gridLayout_4->addWidget(label_2, 1, 3, 1, 2);

        UnitMorality = new QLineEdit(layoutWidget_2);
        UnitMorality->setObjectName("UnitMorality");

        gridLayout_4->addWidget(UnitMorality, 13, 3, 1, 1);

        ChangeItemsButton = new QPushButton(layoutWidget_2);
        ChangeItemsButton->setObjectName("ChangeItemsButton");

        gridLayout_4->addWidget(ChangeItemsButton, 14, 5, 1, 1);

        label_9 = new QLabel(layoutWidget_2);
        label_9->setObjectName("label_9");

        gridLayout_4->addWidget(label_9, 3, 3, 1, 1);

        UnitMoralityChanges = new QLineEdit(layoutWidget_2);
        UnitMoralityChanges->setObjectName("UnitMoralityChanges");

        gridLayout_4->addWidget(UnitMoralityChanges, 13, 4, 1, 1);

        UnitTypes = new QListWidget(layoutWidget_2);
        UnitTypes->setObjectName("UnitTypes");

        gridLayout_4->addWidget(UnitTypes, 16, 3, 1, 1);

        ChoosedUnitTargetType = new QLabel(layoutWidget_2);
        ChoosedUnitTargetType->setObjectName("ChoosedUnitTargetType");

        gridLayout_4->addWidget(ChoosedUnitTargetType, 17, 4, 1, 1);

        ChoosedUnitType = new QLabel(layoutWidget_2);
        ChoosedUnitType->setObjectName("ChoosedUnitType");

        gridLayout_4->addWidget(ChoosedUnitType, 17, 3, 1, 1);

        changeViability = new QLineEdit(layoutWidget_2);
        changeViability->setObjectName("changeViability");

        gridLayout_4->addWidget(changeViability, 9, 3, 1, 2);

        UnitTargetTypes = new QListWidget(layoutWidget_2);
        UnitTargetTypes->setObjectName("UnitTargetTypes");

        gridLayout_4->addWidget(UnitTargetTypes, 16, 4, 1, 1);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName("label_3");

        gridLayout_4->addWidget(label_3, 3, 4, 1, 1);

        DeleteUnitButton = new QPushButton(layoutWidget_2);
        DeleteUnitButton->setObjectName("DeleteUnitButton");

        gridLayout_4->addWidget(DeleteUnitButton, 11, 5, 1, 1);

        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName("label_6");

        gridLayout_4->addWidget(label_6, 14, 4, 1, 1);

        UnitMaxPower = new QLineEdit(layoutWidget_2);
        UnitMaxPower->setObjectName("UnitMaxPower");

        gridLayout_4->addWidget(UnitMaxPower, 5, 4, 1, 1);

        label_7 = new QLabel(layoutWidget_2);
        label_7->setObjectName("label_7");

        gridLayout_4->addWidget(label_7, 10, 3, 1, 1);

        label_1 = new QLabel(layoutWidget_2);
        label_1->setObjectName("label_1");

        gridLayout_4->addWidget(label_1, 0, 0, 1, 2, Qt::AlignmentFlag::AlignHCenter);

        UnitMinPower = new QLineEdit(layoutWidget_2);
        UnitMinPower->setObjectName("UnitMinPower");

        gridLayout_4->addWidget(UnitMinPower, 5, 3, 1, 1);

        UnitNameLineEdit = new QLineEdit(layoutWidget_2);
        UnitNameLineEdit->setObjectName("UnitNameLineEdit");

        gridLayout_4->addWidget(UnitNameLineEdit, 2, 3, 1, 2);

        label_10 = new QLabel(layoutWidget_2);
        label_10->setObjectName("label_10");

        gridLayout_4->addWidget(label_10, 12, 4, 1, 1);

        AddUnit = new QPushButton(layoutWidget_2);
        AddUnit->setObjectName("AddUnit");

        gridLayout_4->addWidget(AddUnit, 8, 5, 1, 1);

        fortificationTargetCheckBox = new QCheckBox(layoutWidget_2);
        fortificationTargetCheckBox->setObjectName("fortificationTargetCheckBox");

        gridLayout_4->addWidget(fortificationTargetCheckBox, 10, 4, 1, 1);

        renovareArmorCheckBox = new QCheckBox(layoutWidget_2);
        renovareArmorCheckBox->setObjectName("renovareArmorCheckBox");

        gridLayout_4->addWidget(renovareArmorCheckBox, 11, 4, 1, 1);


        retranslateUi(AddUnitFormClass);

        QMetaObject::connectSlotsByName(AddUnitFormClass);
    } // setupUi

    void retranslateUi(QDialog *AddUnitFormClass)
    {
        AddUnitFormClass->setWindowTitle(QCoreApplication::translate("AddUnitFormClass", "AddUnitForm", nullptr));
        label_5->setText(QCoreApplication::translate("AddUnitFormClass", "Choose unit type:<b style =\"color:red;\">*</b>", nullptr));
        label_8->setText(QCoreApplication::translate("AddUnitFormClass", "Enter unit morality:", nullptr));
        ToMenu->setText(QCoreApplication::translate("AddUnitFormClass", "Go back", nullptr));
        label_4->setText(QCoreApplication::translate("AddUnitFormClass", "Enter unit health:<b style =\"color:red;\">*</b>", nullptr));
        UnitArmor->setText(QCoreApplication::translate("AddUnitFormClass", "0", nullptr));
        label_2->setText(QCoreApplication::translate("AddUnitFormClass", "Enter unit name:<b style =\"color:red;\">*</b>", nullptr));
        UnitMorality->setText(QString());
        ChangeItemsButton->setText(QCoreApplication::translate("AddUnitFormClass", "Change Items", nullptr));
        label_9->setText(QCoreApplication::translate("AddUnitFormClass", "Enter min base power:<b style =\"color:red;\">*</b>", nullptr));
        UnitMoralityChanges->setText(QString());
        ChoosedUnitTargetType->setText(QString());
        ChoosedUnitType->setText(QString());
        changeViability->setText(QString());
        label_3->setText(QCoreApplication::translate("AddUnitFormClass", "Enter max base power:<b style =\"color:red;\">*</b>", nullptr));
        DeleteUnitButton->setText(QCoreApplication::translate("AddUnitFormClass", "Delete Unit", nullptr));
        label_6->setText(QCoreApplication::translate("AddUnitFormClass", "Choose unit priority target type:<b style =\"color:red;\">*</b>", nullptr));
        UnitMaxPower->setText(QString());
        label_7->setText(QCoreApplication::translate("AddUnitFormClass", "Enter unit armor:", nullptr));
        label_1->setText(QCoreApplication::translate("AddUnitFormClass", "Units", nullptr));
        UnitMinPower->setText(QString());
        label_10->setText(QCoreApplication::translate("AddUnitFormClass", "Enter morality changes rate:", nullptr));
        AddUnit->setText(QCoreApplication::translate("AddUnitFormClass", "Add Unit", nullptr));
        fortificationTargetCheckBox->setText(QCoreApplication::translate("AddUnitFormClass", "Set fortification priority target", nullptr));
        renovareArmorCheckBox->setText(QCoreApplication::translate("AddUnitFormClass", "Renovate armor durng battle?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddUnitFormClass: public Ui_AddUnitFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDUNITFORM_H
