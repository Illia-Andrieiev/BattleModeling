#include "AddCyclingAndPowerCoefForm.h"

AddCyclingAndPowerCoefForm::AddCyclingAndPowerCoefForm(Unit* unit, QWidget *parent)
	: QDialog(parent),unit(unit)
{
	if (unit == nullptr)
		this->close();
	ui.setupUi(this);
}

AddCyclingAndPowerCoefForm::~AddCyclingAndPowerCoefForm()
{}
