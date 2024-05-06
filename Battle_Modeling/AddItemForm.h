#pragma once
#include <QDialog>
#include "ui_AddItemForm.h"
#include"Item.h"
class AddItemForm : public QDialog
{
	Q_OBJECT
private slots:
	void on_AddItemButton_clicked();
	void on_ToMenu_clicked();
	void on_AddPowerCoef_clicked();
	void on_UnitTypes_itemDoubleClicked(QListWidgetItem* item);
	void on_ItemsListWidget_itemDoubleClicked(QListWidgetItem* item);
	void on_DeleteItemButton_clicked();
public:
	AddItemForm(QWidget *parent = nullptr);
	~AddItemForm();

private:
	std::string directoryPath;
	Ui::AddItemFormClass ui;
	Item curItem;
	void fillItemsList();
	void setStyles();
	void writeCurItem();
};
