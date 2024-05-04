#pragma once
#include"MoralUnit.h"
#include <QDialog>
#include "ui_AddCyclingAndPowerCoefForm.h"

class AddCyclingAndPowerCoefForm : public QDialog
{
	Q_OBJECT

public:
	AddCyclingAndPowerCoefForm(Unit* unit,QWidget *parent = nullptr);
	~AddCyclingAndPowerCoefForm();

private:
	Unit* unit;
	Ui::AddCyclingAndPowerCoefFormClass ui;
};
