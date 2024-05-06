/********************************************************************************
** Form generated from reading UI file 'AddCyclingAndPowerCoefForm.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCYCLINGANDPOWERCOEFFORM_H
#define UI_ADDCYCLINGANDPOWERCOEFFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddCyclingAndPowerCoefFormClass
{
public:
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_4;
    QLineEdit *RoundsToActivation;
    QLineEdit *RoundsToReplenishment;
    QListWidget *UnitTypes;
    QPushButton *ToMenu;
    QLabel *label_5;
    QLineEdit *PowerCoef;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *AddPowerCoef;
    QLabel *label_6;
    QPushButton *FinishButton;
    QRadioButton *IsActive;

    void setupUi(QDialog *AddCyclingAndPowerCoefFormClass)
    {
        if (AddCyclingAndPowerCoefFormClass->objectName().isEmpty())
            AddCyclingAndPowerCoefFormClass->setObjectName("AddCyclingAndPowerCoefFormClass");
        AddCyclingAndPowerCoefFormClass->resize(644, 413);
        layoutWidget_2 = new QWidget(AddCyclingAndPowerCoefFormClass);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(0, 0, 641, 411));
        gridLayout_4 = new QGridLayout(layoutWidget_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        RoundsToActivation = new QLineEdit(layoutWidget_2);
        RoundsToActivation->setObjectName("RoundsToActivation");

        gridLayout_4->addWidget(RoundsToActivation, 3, 1, 1, 2);

        RoundsToReplenishment = new QLineEdit(layoutWidget_2);
        RoundsToReplenishment->setObjectName("RoundsToReplenishment");

        gridLayout_4->addWidget(RoundsToReplenishment, 1, 1, 1, 2);

        UnitTypes = new QListWidget(layoutWidget_2);
        UnitTypes->setObjectName("UnitTypes");

        gridLayout_4->addWidget(UnitTypes, 6, 1, 1, 1);

        ToMenu = new QPushButton(layoutWidget_2);
        ToMenu->setObjectName("ToMenu");
        ToMenu->setStyleSheet(QString::fromUtf8("background-color:#F0FFFF;\n"
"font-weight:800;\n"
"color:black;\n"
""));

        gridLayout_4->addWidget(ToMenu, 2, 3, 1, 1);

        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName("label_5");

        gridLayout_4->addWidget(label_5, 5, 1, 1, 1);

        PowerCoef = new QLineEdit(layoutWidget_2);
        PowerCoef->setObjectName("PowerCoef");

        gridLayout_4->addWidget(PowerCoef, 6, 2, 1, 1);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName("label_3");

        gridLayout_4->addWidget(label_3, 2, 1, 1, 2);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName("label_2");

        gridLayout_4->addWidget(label_2, 0, 1, 1, 2);

        AddPowerCoef = new QPushButton(layoutWidget_2);
        AddPowerCoef->setObjectName("AddPowerCoef");

        gridLayout_4->addWidget(AddPowerCoef, 6, 3, 1, 1);

        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName("label_6");

        gridLayout_4->addWidget(label_6, 5, 2, 1, 1);

        FinishButton = new QPushButton(layoutWidget_2);
        FinishButton->setObjectName("FinishButton");

        gridLayout_4->addWidget(FinishButton, 5, 3, 1, 1);

        IsActive = new QRadioButton(layoutWidget_2);
        IsActive->setObjectName("IsActive");

        gridLayout_4->addWidget(IsActive, 4, 1, 1, 1);


        retranslateUi(AddCyclingAndPowerCoefFormClass);

        QMetaObject::connectSlotsByName(AddCyclingAndPowerCoefFormClass);
    } // setupUi

    void retranslateUi(QDialog *AddCyclingAndPowerCoefFormClass)
    {
        AddCyclingAndPowerCoefFormClass->setWindowTitle(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "AddCyclingAndPowerCoefForm", nullptr));
        RoundsToActivation->setText(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "2", nullptr));
        RoundsToReplenishment->setText(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "10", nullptr));
        ToMenu->setText(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "Go back", nullptr));
        label_5->setText(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "Choose type to change:", nullptr));
        PowerCoef->setText(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "1", nullptr));
        label_3->setText(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "Enter Unit`s rounds to activation:<b style =\"color:red;\">*</b>", nullptr));
        label_2->setText(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "Enter Unit`s rounds to replenishment:<b style =\"color:red;\">*</b>", nullptr));
        AddPowerCoef->setText(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "Add power coef", nullptr));
        label_6->setText(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "Enter power coef:", nullptr));
        FinishButton->setText(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "Finish", nullptr));
        IsActive->setText(QCoreApplication::translate("AddCyclingAndPowerCoefFormClass", "Is unit active now", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddCyclingAndPowerCoefFormClass: public Ui_AddCyclingAndPowerCoefFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCYCLINGANDPOWERCOEFFORM_H
