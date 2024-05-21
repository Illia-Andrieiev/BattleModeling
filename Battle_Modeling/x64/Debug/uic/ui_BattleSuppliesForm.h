/********************************************************************************
** Form generated from reading UI file 'BattleSuppliesForm.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATTLESUPPLIESFORM_H
#define UI_BATTLESUPPLIESFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BattleSuppliesFormClass
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_10;
    QLineEdit *Army1RoundSupplies;
    QLabel *label_11;
    QLineEdit *Army2RoundSupplies;
    QLabel *label_13;
    QLineEdit *Army1AmountRounds;
    QLabel *label_12;
    QLineEdit *Army2AmountRounds;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QLabel *label_8;
    QLineEdit *Army1supplies;
    QLabel *label_9;
    QLineEdit *Army2supplies;
    QLabel *label_3;
    QPushButton *ToMenu;
    QPushButton *ApplySupplies;

    void setupUi(QDialog *BattleSuppliesFormClass)
    {
        if (BattleSuppliesFormClass->objectName().isEmpty())
            BattleSuppliesFormClass->setObjectName("BattleSuppliesFormClass");
        BattleSuppliesFormClass->resize(761, 360);
        gridLayoutWidget = new QWidget(BattleSuppliesFormClass);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 0, 631, 361));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName("label_10");

        verticalLayout_3->addWidget(label_10);

        Army1RoundSupplies = new QLineEdit(gridLayoutWidget);
        Army1RoundSupplies->setObjectName("Army1RoundSupplies");

        verticalLayout_3->addWidget(Army1RoundSupplies);

        label_11 = new QLabel(gridLayoutWidget);
        label_11->setObjectName("label_11");

        verticalLayout_3->addWidget(label_11);

        Army2RoundSupplies = new QLineEdit(gridLayoutWidget);
        Army2RoundSupplies->setObjectName("Army2RoundSupplies");

        verticalLayout_3->addWidget(Army2RoundSupplies);

        label_13 = new QLabel(gridLayoutWidget);
        label_13->setObjectName("label_13");

        verticalLayout_3->addWidget(label_13);

        Army1AmountRounds = new QLineEdit(gridLayoutWidget);
        Army1AmountRounds->setObjectName("Army1AmountRounds");

        verticalLayout_3->addWidget(Army1AmountRounds);

        label_12 = new QLabel(gridLayoutWidget);
        label_12->setObjectName("label_12");

        verticalLayout_3->addWidget(label_12);

        Army2AmountRounds = new QLineEdit(gridLayoutWidget);
        Army2AmountRounds->setObjectName("Army2AmountRounds");

        verticalLayout_3->addWidget(Army2AmountRounds);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);


        gridLayout->addLayout(verticalLayout_3, 0, 3, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName("label_8");

        verticalLayout->addWidget(label_8);

        Army1supplies = new QLineEdit(gridLayoutWidget);
        Army1supplies->setObjectName("Army1supplies");

        verticalLayout->addWidget(Army1supplies);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName("label_9");

        verticalLayout->addWidget(label_9);

        Army2supplies = new QLineEdit(gridLayoutWidget);
        Army2supplies->setObjectName("Army2supplies");

        verticalLayout->addWidget(Army2supplies);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        ToMenu = new QPushButton(BattleSuppliesFormClass);
        ToMenu->setObjectName("ToMenu");
        ToMenu->setGeometry(QRect(640, 80, 111, 24));
        ToMenu->setStyleSheet(QString::fromUtf8("background-color:#F0FFFF;\n"
"font-weight:800;\n"
"color:black;\n"
""));
        ApplySupplies = new QPushButton(BattleSuppliesFormClass);
        ApplySupplies->setObjectName("ApplySupplies");
        ApplySupplies->setGeometry(QRect(640, 230, 111, 24));

        retranslateUi(BattleSuppliesFormClass);

        QMetaObject::connectSlotsByName(BattleSuppliesFormClass);
    } // setupUi

    void retranslateUi(QDialog *BattleSuppliesFormClass)
    {
        BattleSuppliesFormClass->setWindowTitle(QCoreApplication::translate("BattleSuppliesFormClass", "BattleSuppliesForm", nullptr));
        label->setText(QString());
        label_10->setText(QCoreApplication::translate("BattleSuppliesFormClass", "Army 1 supplies per round: ", nullptr));
        Army1RoundSupplies->setText(QCoreApplication::translate("BattleSuppliesFormClass", "0", nullptr));
        label_11->setText(QCoreApplication::translate("BattleSuppliesFormClass", "Army 2 supplies per round: ", nullptr));
        Army2RoundSupplies->setText(QCoreApplication::translate("BattleSuppliesFormClass", "0", nullptr));
        label_13->setText(QCoreApplication::translate("BattleSuppliesFormClass", "How many rounds add supplies for army 1: ", nullptr));
        Army1AmountRounds->setText(QCoreApplication::translate("BattleSuppliesFormClass", "0", nullptr));
        label_12->setText(QCoreApplication::translate("BattleSuppliesFormClass", "How many rounds add supplies for army 1: ", nullptr));
        Army2AmountRounds->setText(QCoreApplication::translate("BattleSuppliesFormClass", "0", nullptr));
        label_2->setText(QString());
        label_4->setText(QString());
        label_8->setText(QCoreApplication::translate("BattleSuppliesFormClass", "Army 1 start supplies: ", nullptr));
        Army1supplies->setText(QCoreApplication::translate("BattleSuppliesFormClass", "0", nullptr));
        label_9->setText(QCoreApplication::translate("BattleSuppliesFormClass", "Army 2 start supplies: ", nullptr));
        Army2supplies->setText(QCoreApplication::translate("BattleSuppliesFormClass", "0", nullptr));
        label_3->setText(QString());
        ToMenu->setText(QCoreApplication::translate("BattleSuppliesFormClass", "Start modeling", nullptr));
        ApplySupplies->setText(QCoreApplication::translate("BattleSuppliesFormClass", "Apply supplies", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BattleSuppliesFormClass: public Ui_BattleSuppliesFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATTLESUPPLIESFORM_H
