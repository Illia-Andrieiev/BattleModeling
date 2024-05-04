#include "AddUnitForm.h"
#include"AddCyclingAndPowerCoefForm.h"
AddUnitForm::AddUnitForm(QWidget *parent)
	: QDialog(parent)
{
	
	ui.setupUi(this);
}

AddUnitForm::~AddUnitForm()
{}
void AddUnitForm::on_AddUnit_clicked() {
	//MoralUnitBuilder build;
	AddCyclingAndPowerCoefForm w;
	w.setModal(true);
	w.exec();
}