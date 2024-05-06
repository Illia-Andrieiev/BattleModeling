#pragma once

#include <QDialog>
#include "ui_AddArmyForm.h"
#include "Army.h"
class AddArmyForm : public QDialog
{
	Q_OBJECT

public:
	AddArmyForm(QWidget *parent = nullptr);
	AddArmyForm(QString armyName,QWidget* parent = nullptr);
	~AddArmyForm();
private slots:
	void on_UnitsListWidget_itemDoubleClicked(QListWidgetItem* item);
	void on_ToMenu_clicked(); 
	void on_AddUnitButton_clicked();
	void on_AddFortificationButton_clicked();
	void on_AddArmyButton_clicked(); 
	void on_DeleteUnitButton_clicked();
	void on_DeleteFortificationButton_clicked();
	void on_DeleteArmyButton_clicked();
	void on_ArmiesListWidget_itemDoubleClicked(QListWidgetItem* item);
private:
	void writeCurArmy();
	Ui::AddArmyFormClass ui;
	Army curArmy;
	void fillArmyUnits();
	void setStyles();
};
