#pragma once
#include <QDialog>
#include "ui_AddCircumstanceForm.h"
#include "Circumstance.h"
class AddCircumstanceForm : public QDialog
{
	Q_OBJECT

public:
	AddCircumstanceForm(QWidget *parent = nullptr);
	~AddCircumstanceForm();
private:
	Ui::AddCircumstanceFormClass ui;
private slots:
	void on_AddCircumstanceButton_clicked();
	void on_ToMenu_clicked();
	void on_AddPowerCoef_clicked();
	void on_UnitTypes_itemDoubleClicked(QListWidgetItem* item);
	void on_CircumstancesListWidget_itemDoubleClicked(QListWidgetItem* item);
	void on_DeleteCircumstanceButton_clicked();
private:
	Circumstance curCircumstance;
	std::string directoryPath;
	void fillCicumstancesList();
	void setStyles();
	void writeCurCirc();
};
