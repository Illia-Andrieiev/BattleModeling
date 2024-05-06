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
	void on_UnitsListWidget_itemDoubleClicked(QListWidgetItem* item);
	void on_DeleteUnitButton_clicked();
	void on_AddUnit_clicked();
	void on_ChangeItemsButton_clicked();
private:
	std::shared_ptr<Unit> readUnit();
	std::string directoryPath;
	std::shared_ptr<Unit> curUnit;
	bool isDataCorrect();
	void fillUnitsList();
	void setStyles();
	Ui::AddUnitFormClass ui;
};
