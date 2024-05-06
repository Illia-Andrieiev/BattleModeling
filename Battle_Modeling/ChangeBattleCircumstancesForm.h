#pragma once

#include <QDialog>
#include "ui_ChangeBattleCircumstancesForm.h"
#include"BattleModeling.h"
class ChangeBattleCircumstancesForm : public QDialog
{
	Q_OBJECT

public:
	ChangeBattleCircumstancesForm(BattleModeling& battle,QWidget *parent = nullptr);
	~ChangeBattleCircumstancesForm();
private slots:
	void on_ApplyCircButton_clicked();
	void on_ToMenu_clicked();
	void on_AppliedCircs_itemDoubleClicked(QListWidgetItem* item);
	void on_CircListWidget_itemDoubleClicked(QListWidgetItem* item);
	void on_RemoveGeneralCircButton_clicked();
	void on_ApplySpecialCircs_clicked();
	
private:
	BattleModeling& battle;
	bool isCircExist(QString name);
	void setStyles();
	Circumstance readCirc(std::string name);
	Ui::ChangeBattleCircumstancesFormClass ui;
};
