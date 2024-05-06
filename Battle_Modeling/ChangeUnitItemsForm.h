#pragma once

#include <QDialog>
#include "ui_ChangeUnitItemsForm.h"
#include"Unit.h"
class ChangeUnitItemsForm : public QDialog
{
	Q_OBJECT

public:
	ChangeUnitItemsForm(std::shared_ptr<Unit> unit,QWidget *parent = nullptr);
	~ChangeUnitItemsForm();
private slots:
	void on_ApplyItemButton_clicked();
	void on_ToMenu_clicked();
	void on_AppliedItems_itemDoubleClicked(QListWidgetItem* item);
	void on_ItemsListWidget_itemDoubleClicked(QListWidgetItem* item);
	void on_RemoveItemButton_clicked();
private:
	std::shared_ptr<Unit> unit;
	Ui::ChangeUnitItemsFormClass ui;
	void setStyles();
};
