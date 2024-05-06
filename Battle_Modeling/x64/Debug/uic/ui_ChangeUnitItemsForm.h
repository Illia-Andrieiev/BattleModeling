/********************************************************************************
** Form generated from reading UI file 'ChangeUnitItemsForm.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEUNITITEMSFORM_H
#define UI_CHANGEUNITITEMSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeUnitItemsFormClass
{
public:
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_4;
    QLabel *label_5;
    QListWidget *AppliedItems;
    QLabel *label_1;
    QListWidget *ItemsListWidget;
    QPushButton *RemoveItemButton;
    QPushButton *ToMenu;
    QPushButton *ApplyItemButton;

    void setupUi(QDialog *ChangeUnitItemsFormClass)
    {
        if (ChangeUnitItemsFormClass->objectName().isEmpty())
            ChangeUnitItemsFormClass->setObjectName("ChangeUnitItemsFormClass");
        ChangeUnitItemsFormClass->resize(783, 417);
        layoutWidget_2 = new QWidget(ChangeUnitItemsFormClass);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(0, 10, 781, 411));
        gridLayout_4 = new QGridLayout(layoutWidget_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName("label_5");

        gridLayout_4->addWidget(label_5, 0, 3, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        AppliedItems = new QListWidget(layoutWidget_2);
        AppliedItems->setObjectName("AppliedItems");
        AppliedItems->setMinimumSize(QSize(478, 356));

        gridLayout_4->addWidget(AppliedItems, 3, 3, 8, 1);

        label_1 = new QLabel(layoutWidget_2);
        label_1->setObjectName("label_1");

        gridLayout_4->addWidget(label_1, 0, 0, 1, 2, Qt::AlignmentFlag::AlignHCenter);

        ItemsListWidget = new QListWidget(layoutWidget_2);
        ItemsListWidget->setObjectName("ItemsListWidget");

        gridLayout_4->addWidget(ItemsListWidget, 3, 0, 8, 2);

        RemoveItemButton = new QPushButton(layoutWidget_2);
        RemoveItemButton->setObjectName("RemoveItemButton");

        gridLayout_4->addWidget(RemoveItemButton, 8, 4, 1, 1);

        ToMenu = new QPushButton(layoutWidget_2);
        ToMenu->setObjectName("ToMenu");
        ToMenu->setStyleSheet(QString::fromUtf8("background-color:#F0FFFF;\n"
"font-weight:800;\n"
"color:black;\n"
""));

        gridLayout_4->addWidget(ToMenu, 4, 4, 1, 1);

        ApplyItemButton = new QPushButton(layoutWidget_2);
        ApplyItemButton->setObjectName("ApplyItemButton");

        gridLayout_4->addWidget(ApplyItemButton, 6, 4, 1, 1);


        retranslateUi(ChangeUnitItemsFormClass);

        QMetaObject::connectSlotsByName(ChangeUnitItemsFormClass);
    } // setupUi

    void retranslateUi(QDialog *ChangeUnitItemsFormClass)
    {
        ChangeUnitItemsFormClass->setWindowTitle(QCoreApplication::translate("ChangeUnitItemsFormClass", "ChangeUnitItemsForm", nullptr));
        label_5->setText(QCoreApplication::translate("ChangeUnitItemsFormClass", "Applied items", nullptr));
        label_1->setText(QCoreApplication::translate("ChangeUnitItemsFormClass", "Items", nullptr));
        RemoveItemButton->setText(QCoreApplication::translate("ChangeUnitItemsFormClass", "Remove Item", nullptr));
        ToMenu->setText(QCoreApplication::translate("ChangeUnitItemsFormClass", "Go back", nullptr));
        ApplyItemButton->setText(QCoreApplication::translate("ChangeUnitItemsFormClass", "Apply Item", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeUnitItemsFormClass: public Ui_ChangeUnitItemsFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEUNITITEMSFORM_H
