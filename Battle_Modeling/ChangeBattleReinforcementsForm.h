#pragma once

#include <QDialog>
#include "ui_ChangeBattleReinforcementsForm.h"
#include"BattleModeling.h"
class ChangeBattleReinforcementsForm : public QDialog
{
	Q_OBJECT

public:
	ChangeBattleReinforcementsForm(BattleBuilder& builder,QWidget *parent = nullptr);
	~ChangeBattleReinforcementsForm();
private slots:
	void on_ApplyReinf_clicked();
	void on_ToMenu_clicked();
	void on_ArmiesListWidget_itemDoubleClicked(QListWidgetItem* item);
private:
	BattleBuilder& builder;
	void setStyles();
	bool isReinfExist(QString name);
	Ui::ChangeBattleReinforcementsFormClass ui;
};
