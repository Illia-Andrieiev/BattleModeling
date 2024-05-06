/********************************************************************************
** Form generated from reading UI file 'ChangeBattleCircumstancesForm.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEBATTLECIRCUMSTANCESFORM_H
#define UI_CHANGEBATTLECIRCUMSTANCESFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeBattleCircumstancesFormClass
{
public:
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_4;
    QListWidget *CircListWidget;
    QLabel *label_1;
    QListWidget *AppliedCircs;
    QVBoxLayout *verticalLayout;
    QPushButton *ToMenu;
    QPushButton *ApplyCircButton;
    QPushButton *ApplySpecialCircs;
    QPushButton *RemoveGeneralCircButton;
    QLabel *label_5;
    QLabel *label;
    QLineEdit *Army1Circ;
    QLabel *label_2;
    QLineEdit *Army2Circ;

    void setupUi(QDialog *ChangeBattleCircumstancesFormClass)
    {
        if (ChangeBattleCircumstancesFormClass->objectName().isEmpty())
            ChangeBattleCircumstancesFormClass->setObjectName("ChangeBattleCircumstancesFormClass");
        ChangeBattleCircumstancesFormClass->resize(919, 416);
        layoutWidget_2 = new QWidget(ChangeBattleCircumstancesFormClass);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(0, 0, 914, 411));
        gridLayout_4 = new QGridLayout(layoutWidget_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        CircListWidget = new QListWidget(layoutWidget_2);
        CircListWidget->setObjectName("CircListWidget");

        gridLayout_4->addWidget(CircListWidget, 1, 0, 6, 3);

        label_1 = new QLabel(layoutWidget_2);
        label_1->setObjectName("label_1");

        gridLayout_4->addWidget(label_1, 0, 0, 1, 3, Qt::AlignmentFlag::AlignHCenter);

        AppliedCircs = new QListWidget(layoutWidget_2);
        AppliedCircs->setObjectName("AppliedCircs");

        gridLayout_4->addWidget(AppliedCircs, 1, 3, 6, 1);

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

        ApplyCircButton = new QPushButton(layoutWidget_2);
        ApplyCircButton->setObjectName("ApplyCircButton");

        verticalLayout->addWidget(ApplyCircButton);

        ApplySpecialCircs = new QPushButton(layoutWidget_2);
        ApplySpecialCircs->setObjectName("ApplySpecialCircs");

        verticalLayout->addWidget(ApplySpecialCircs);

        RemoveGeneralCircButton = new QPushButton(layoutWidget_2);
        RemoveGeneralCircButton->setObjectName("RemoveGeneralCircButton");

        verticalLayout->addWidget(RemoveGeneralCircButton);


        gridLayout_4->addLayout(verticalLayout, 0, 5, 7, 1);

        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName("label_5");

        gridLayout_4->addWidget(label_5, 0, 3, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label = new QLabel(layoutWidget_2);
        label->setObjectName("label");

        gridLayout_4->addWidget(label, 1, 4, 1, 1);

        Army1Circ = new QLineEdit(layoutWidget_2);
        Army1Circ->setObjectName("Army1Circ");

        gridLayout_4->addWidget(Army1Circ, 2, 4, 1, 1);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName("label_2");

        gridLayout_4->addWidget(label_2, 3, 4, 1, 1);

        Army2Circ = new QLineEdit(layoutWidget_2);
        Army2Circ->setObjectName("Army2Circ");

        gridLayout_4->addWidget(Army2Circ, 4, 4, 1, 1);


        retranslateUi(ChangeBattleCircumstancesFormClass);

        QMetaObject::connectSlotsByName(ChangeBattleCircumstancesFormClass);
    } // setupUi

    void retranslateUi(QDialog *ChangeBattleCircumstancesFormClass)
    {
        ChangeBattleCircumstancesFormClass->setWindowTitle(QCoreApplication::translate("ChangeBattleCircumstancesFormClass", "ChangeBattleCircumstancesForm", nullptr));
        label_1->setText(QCoreApplication::translate("ChangeBattleCircumstancesFormClass", "Circumstances", nullptr));
        ToMenu->setText(QCoreApplication::translate("ChangeBattleCircumstancesFormClass", "Go back", nullptr));
        ApplyCircButton->setText(QCoreApplication::translate("ChangeBattleCircumstancesFormClass", "Apply circumstance", nullptr));
        ApplySpecialCircs->setText(QCoreApplication::translate("ChangeBattleCircumstancesFormClass", "Apply special", nullptr));
        RemoveGeneralCircButton->setText(QCoreApplication::translate("ChangeBattleCircumstancesFormClass", "remove general", nullptr));
        label_5->setText(QCoreApplication::translate("ChangeBattleCircumstancesFormClass", "General circumstances ", nullptr));
        label->setText(QCoreApplication::translate("ChangeBattleCircumstancesFormClass", "Army 1 special circumstance:", nullptr));
        label_2->setText(QCoreApplication::translate("ChangeBattleCircumstancesFormClass", "Army 2 special circumstance:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeBattleCircumstancesFormClass: public Ui_ChangeBattleCircumstancesFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEBATTLECIRCUMSTANCESFORM_H
