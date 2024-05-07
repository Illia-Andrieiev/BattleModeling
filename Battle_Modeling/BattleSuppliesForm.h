#pragma once
#include"BattleModeling.h"
#include <QDialog>
#include "ui_BattleSuppliesForm.h"

class BattleSuppliesForm : public QDialog
{
	Q_OBJECT

public:
	BattleSuppliesForm(BattleBuilder& builder, QWidget *parent = nullptr);
	~BattleSuppliesForm();
private slots:
	void on_ToMenu_clicked();
	void on_ApplySupplies_clicked();
private:
	void setStyles();
	BattleBuilder& builder;
	Ui::BattleSuppliesFormClass ui;
};
