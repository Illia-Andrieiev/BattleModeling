/********************************************************************************
** Form generated from reading UI file 'ChangeBattleReinforcementsForm.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEBATTLEREINFORCEMENTSFORM_H
#define UI_CHANGEBATTLEREINFORCEMENTSFORM_H

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

class Ui_ChangeBattleReinforcementsFormClass
{
public:
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_1;
    QVBoxLayout *verticalLayout;
    QPushButton *ToMenu;
    QPushButton *ApplyReinf;
    QLineEdit *Army1Reinf;
    QListWidget *ArmiesListWidget;
    QLineEdit *Army2Reinf;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *Army1Percents;
    QLineEdit *Army2Percents;

    void setupUi(QDialog *ChangeBattleReinforcementsFormClass)
    {
        if (ChangeBattleReinforcementsFormClass->objectName().isEmpty())
            ChangeBattleReinforcementsFormClass->setObjectName("ChangeBattleReinforcementsFormClass");
        ChangeBattleReinforcementsFormClass->resize(914, 410);
        layoutWidget_2 = new QWidget(ChangeBattleReinforcementsFormClass);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(0, 0, 914, 411));
        gridLayout_4 = new QGridLayout(layoutWidget_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget_2);
        label->setObjectName("label");

        gridLayout_4->addWidget(label, 1, 4, 1, 1);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName("label_2");

        gridLayout_4->addWidget(label_2, 3, 4, 1, 1);

        label_1 = new QLabel(layoutWidget_2);
        label_1->setObjectName("label_1");

        gridLayout_4->addWidget(label_1, 0, 0, 1, 3, Qt::AlignmentFlag::AlignHCenter);

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

        ApplyReinf = new QPushButton(layoutWidget_2);
        ApplyReinf->setObjectName("ApplyReinf");

        verticalLayout->addWidget(ApplyReinf);


        gridLayout_4->addLayout(verticalLayout, 0, 5, 6, 1);

        Army1Reinf = new QLineEdit(layoutWidget_2);
        Army1Reinf->setObjectName("Army1Reinf");

        gridLayout_4->addWidget(Army1Reinf, 2, 4, 1, 1);

        ArmiesListWidget = new QListWidget(layoutWidget_2);
        ArmiesListWidget->setObjectName("ArmiesListWidget");

        gridLayout_4->addWidget(ArmiesListWidget, 1, 0, 5, 3);

        Army2Reinf = new QLineEdit(layoutWidget_2);
        Army2Reinf->setObjectName("Army2Reinf");

        gridLayout_4->addWidget(Army2Reinf, 4, 4, 1, 1);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName("label_3");

        gridLayout_4->addWidget(label_3, 1, 3, 1, 1);

        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName("label_4");

        gridLayout_4->addWidget(label_4, 3, 3, 1, 1);

        Army1Percents = new QLineEdit(layoutWidget_2);
        Army1Percents->setObjectName("Army1Percents");

        gridLayout_4->addWidget(Army1Percents, 2, 3, 1, 1);

        Army2Percents = new QLineEdit(layoutWidget_2);
        Army2Percents->setObjectName("Army2Percents");

        gridLayout_4->addWidget(Army2Percents, 4, 3, 1, 1);


        retranslateUi(ChangeBattleReinforcementsFormClass);

        QMetaObject::connectSlotsByName(ChangeBattleReinforcementsFormClass);
    } // setupUi

    void retranslateUi(QDialog *ChangeBattleReinforcementsFormClass)
    {
        ChangeBattleReinforcementsFormClass->setWindowTitle(QCoreApplication::translate("ChangeBattleReinforcementsFormClass", "ChangeBattleReinforcementsForm", nullptr));
        label->setText(QCoreApplication::translate("ChangeBattleReinforcementsFormClass", "Army 1 reinforcement:", nullptr));
        label_2->setText(QCoreApplication::translate("ChangeBattleReinforcementsFormClass", "Army 2 reinforcement:", nullptr));
        label_1->setText(QCoreApplication::translate("ChangeBattleReinforcementsFormClass", "Armies", nullptr));
        ToMenu->setText(QCoreApplication::translate("ChangeBattleReinforcementsFormClass", "Go back", nullptr));
        ApplyReinf->setText(QCoreApplication::translate("ChangeBattleReinforcementsFormClass", "Apply reinforcements", nullptr));
        label_3->setText(QCoreApplication::translate("ChangeBattleReinforcementsFormClass", "Persent of army 1 reinforcement for 1 round", nullptr));
        label_4->setText(QCoreApplication::translate("ChangeBattleReinforcementsFormClass", "Persent of army 2 reinforcement for 1 round", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeBattleReinforcementsFormClass: public Ui_ChangeBattleReinforcementsFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEBATTLEREINFORCEMENTSFORM_H
