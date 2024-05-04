#pragma once

#include <QDialog>
#include "ui_AddUnitForm.h"
#include"MoralUnit.h"
class AddUnitForm : public QDialog
{
	Q_OBJECT

public:
	AddUnitForm(QWidget *parent = nullptr);
	~AddUnitForm();
private slots:
	void on_ToMenu_clicked();
	void on_UnitTypes_itemClicked(QListWidgetItem* item);
	void on_UnitTargetTypes_itemClicked(QListWidgetItem* item);
	//void on_UnitsListWidget_itemDoubleClicked(QListWidgetItem* item);
	//void on_DeleteItemButton_clicked();
	void on_AddUnit_clicked();
private:
	std::string directoryPath;
	bool isDataCorrect();
	Unit* curUnit;
	void fillUnitsList();
	void setStyles();
	void writeCurUnit();
	Ui::AddUnitFormClass ui;
};
