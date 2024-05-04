#include "AddUnitForm.h"
#include"AddCyclingAndPowerCoefForm.h"
#include"FileManager.h"
#include<qregularexpression.h>
#include<qmessagebox.h>
#include<filesystem>
#include "UIHelpers.h"
AddUnitForm::AddUnitForm(QWidget *parent)
	: QDialog(parent)
{
	curUnit = nullptr;
	directoryPath = "DataBase\\Units\\";
	ui.setupUi(this);
	ui.UnitNameLineEdit->setMaxLength(256);
	QRegularExpression rx("[^/'\":;]*");
	QRegularExpression pos("\\d+\\.?\\d+");
	QValidator* validatorName = new QRegularExpressionValidator(rx, this);
	ui.UnitNameLineEdit->setValidator(validatorName);
	QValidator* ValidatorDoublePositive = new QRegularExpressionValidator(pos, this);
	ui.UnitMinPower->setValidator(ValidatorDoublePositive);
	ui.UnitMaxPower->setValidator(ValidatorDoublePositive);
	ui.UnitMorality->setValidator(ValidatorDoublePositive);
	ui.UnitArmor->setValidator(ValidatorDoublePositive);
	ui.UnitMoralityChanges->setValidator(ValidatorDoublePositive);
	ui.changeViability->setValidator(ValidatorDoublePositive);
	uiFunctions::fillTypes(ui.UnitTypes);
	fillUnitsList();
	this->setFixedSize(this->size());
	setStyles();
}
AddUnitForm::~AddUnitForm()
{}
bool AddUnitForm::isDataCorrect() {
	QString unitName = ui.UnitNameLineEdit->text();
	if (unitName.isEmpty()) {
		QMessageBox::warning(this, "warning", "Enter unit name!");
		return false;
	}
	QString minPowerStr = ui.UnitMinPower->text();
	if (minPowerStr.isEmpty()) {
		QMessageBox::warning(this, "warning", "Enter unit min power!");
		return false;
	}

	QString maxPowerStr = ui.UnitMaxPower->text();
	if (maxPowerStr.isEmpty()) {
		QMessageBox::warning(this, "warning", "Enter unit max power!");
		return false;
	}
	if (maxPowerStr.toDouble() == 0) {
		QMessageBox::warning(this, "warning", "Unit`s max power cannot be 0!");
		return false;
	}
	if (minPowerStr.toDouble() > maxPowerStr.toDouble()) {
		QMessageBox::warning(this, "warning", "Unit`s max power cannot be less then min power!");
		return false;
	}
	QString viabilityStr = ui.changeViability->text();
	if (viabilityStr.isEmpty()) {
		QMessageBox::warning(this, "warning", "Enter unit health!");
		return false;
	}
	if (viabilityStr.toDouble() == 0) {
		QMessageBox::warning(this, "warning", "Unit`s health cannot be 0!");
		return false;
	}
	if (ui.UnitTypes->currentRow() == -1) {
		QMessageBox::warning(this, "warning", "Choose unit type!");
		return false;
	}
	if (ui.UnitTargetTypes->currentRow() == -1) {
		QMessageBox::warning(this, "warning", "Choose unit priority target type!");
		return false;
	}
	return true;
}
void AddUnitForm::on_AddUnit_clicked() {
	if (!isDataCorrect())
		return;
	std::string unitName = ui.UnitNameLineEdit->text().toStdString();
	double minPower = ui.UnitMinPower->text().toDouble();
	double maxPower = ui.UnitMaxPower->text().toDouble();
	double viability = ui.changeViability->text().toDouble();
	double armor = ui.UnitArmor->text().toDouble();
	bool isRenovateArmor = ui.renovareArmorRadioButton->isChecked();
//	BaseUnitBuilder* builder;
	if (ui.UnitMorality->text().isEmpty()|| ui.UnitMorality->text().toDouble()==0) {
		UnitBuilder* build = new UnitBuilder();
		//build->setArmor(armor,isRenovateArmor)->set
		//builder = build;

	}
	//double morality = std::stod(ui.ItemPower->text().toStdString());
	AddCyclingAndPowerCoefForm w;
	w.setModal(true);
	w.exec();
//	delete builder;
}
void AddUnitForm::on_ToMenu_clicked() {
	this->close();
}
void AddUnitForm::setStyles() {
	ui.AddUnit->setStyleSheet(styles::mainButton);
	ui.ToMenu->setStyleSheet(styles::mainButton);
	ui.DeleteUnitButton->setStyleSheet(styles::elseButtons);
	ui.ChangeItemsButton->setStyleSheet(styles::elseButtons);
}
void AddUnitForm::fillUnitsList() {
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(directoryPath)) {
		ui.UnitsListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
	}
}
void AddUnitForm::on_UnitTypes_itemClicked(QListWidgetItem* item) {
	ui.ChoosedUnitType->setText(item->text());
}
void AddUnitForm::on_UnitTargetTypes_itemClicked(QListWidgetItem* item) {
	ui.ChoosedUnitTargetType->setText(item->text());
}
void AddUnitForm::writeCurUnit() {
	//std::string fileName = directoryPath + curUnit->getName();
	//std::filesystem::remove(fileName);
	//double powerChanges = std::stod(ui.ItemPower->text().toStdString());
	//double viabilityChanges = std::stod(ui.changeViability->text().toStdString());
	//curItem.setViabilityChanges(viabilityChanges);
	//curItem.setBasePowerChanges(powerChanges);
	//std::fstream stream;
	//stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	//FileManager f;
	//f.writeItem(curItem, stream);
	//stream.close();
	//ui.ItemsListWidget->addItem(QString::fromStdString(curItem.getName()));
}