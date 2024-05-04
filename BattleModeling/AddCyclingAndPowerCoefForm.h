#pragma once
#include"MoralUnit.h"
#include <QDialog>
#include "ui_AddCyclingAndPowerCoefForm.h"

class AddCyclingAndPowerCoefForm : public QDialog
{
	Q_OBJECT

public:
	AddCyclingAndPowerCoefForm(QWidget *parent = nullptr);
	~AddCyclingAndPowerCoefForm();

private:
	BaseUnitBuilder& build;
	Ui::AddCyclingAndPowerCoefFormClass ui;
};
