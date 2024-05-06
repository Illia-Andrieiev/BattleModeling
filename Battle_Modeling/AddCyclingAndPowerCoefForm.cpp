#include "AddCyclingAndPowerCoefForm.h"
#include<qmessagebox.h>
#include<filesystem>
#include"FileManager.h"
#include"UIHelpers.h"
AddCyclingAndPowerCoefForm::AddCyclingAndPowerCoefForm(std::shared_ptr<Unit> unit,std::string fileName,bool& isWrited, QWidget *parent)
	: QDialog(parent),unit(unit), isWrited(isWrited)
{
	ui.setupUi(this);
	QRegularExpression pos("\\d+");
	QRegularExpression doubl("\\d+\\.?\\d+");
	QValidator* Validator = new QRegularExpressionValidator(pos, this);
	QValidator* Validator2 = new QRegularExpressionValidator(doubl, this);
	ui.RoundsToActivation->setValidator(Validator);
	ui.RoundsToReplenishment->setValidator(Validator);
	ui.PowerCoef->setValidator(Validator2);
	uiFunctions::fillTypes(ui.UnitTypes);
	ui.RoundsToActivation->setText(QString::number(unit->getCycling().cyclesToActivation));
	ui.RoundsToReplenishment->setText(QString::number(unit->getCycling().cyclesToReplenishment));
	ui.IsActive->setChecked(unit->getCycling().isActive);
	this->fileName = fileName;
	setStyles();
	this->setFixedSize(this->size());
}

AddCyclingAndPowerCoefForm::~AddCyclingAndPowerCoefForm()
{}
void AddCyclingAndPowerCoefForm::on_UnitTypes_itemDoubleClicked(QListWidgetItem* item) {
	int pos = ui.UnitTypes->row(item);
	if (pos == -1)
		return;
	else {
		try {
			double coef = unit->getPowerCoef().at(static_cast<unitHelpers::unitTypes>(pos));
			ui.PowerCoef->setText(QString::fromStdString(std::to_string(coef)));
		}
		catch (const std::out_of_range&) {
			ui.PowerCoef->setText(QString::fromStdString(std::to_string(1)));
		}

	}
}
void AddCyclingAndPowerCoefForm::on_FinishButton_clicked() {
	int toActivation = ui.RoundsToActivation->text().toInt();
	int toRep = ui.RoundsToReplenishment->text().toInt();
	unitHelpers::Cycling cycle(toRep, toActivation, ui.IsActive->isChecked());
	unit->setCycling(cycle);
	writeCurUnit();
	this->close();
}
void AddCyclingAndPowerCoefForm::on_ToMenu_clicked() {
	this->close();
}
void AddCyclingAndPowerCoefForm::on_AddPowerCoef_clicked() {
	int cur = ui.UnitTypes->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose unit type!");
		return;
	}
	unit->setPowerCoef(std::pair<unitHelpers::unitTypes, double>
		(static_cast<unitHelpers::unitTypes>(cur),
			std::stod(ui.PowerCoef->text().toStdString())));
}
void AddCyclingAndPowerCoefForm::writeCurUnit() {
	std::filesystem::remove(fileName);
	std::fstream stream;
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	FileManager f;
	f.writeUnit(unit.get(),1, stream);
	stream.close();
	isWrited = true;
}
void AddCyclingAndPowerCoefForm::setStyles() {
	ui.ToMenu->setStyleSheet(styles::mainButton);
	ui.FinishButton->setStyleSheet(styles::mainButton);
	ui.AddPowerCoef->setStyleSheet(styles::elseButtons);

}