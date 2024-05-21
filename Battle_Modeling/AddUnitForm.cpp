#include "AddUnitForm.h"
#include"AddCyclingAndPowerCoefForm.h"
#include"FileManager.h"
#include<qregularexpression.h>
#include<qmessagebox.h>
#include<filesystem>
#include "UIHelpers.h"
#include "ChangeUnitItemsForm.h"
AddUnitForm::AddUnitForm(QWidget *parent)
	: QDialog(parent)
{
	curUnit = std::make_shared<Unit>();
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
	uiFunctions::fillTypes(ui.UnitTargetTypes);
	fillUnitsList();
	this->setFixedSize(this->size());
	setStyles();
	/*connect(ui.AddUnit, &QPushButton::clicked, this, &AddUnitForm::on_AddUnit_clicked);
	connect(ui.ToMenu, &QPushButton::clicked, this, &AddUnitForm::on_ToMenu_clicked);
	connect(ui.DeleteUnitButton, &QPushButton::clicked, this, &AddUnitForm::on_DeleteUnitButton_clicked);
	connect(ui.UnitTypes, &QListWidget::itemClicked, this, &AddUnitForm::on_UnitTypes_itemClicked);
	connect(ui.UnitTargetTypes, &QListWidget::itemClicked, this, &AddUnitForm::on_UnitTargetTypes_itemClicked);
	connect(ui.UnitsListWidget, &QListWidget::itemDoubleClicked, this, &AddUnitForm::on_UnitsListWidget_itemDoubleClicked);*/
}
AddUnitForm::~AddUnitForm()
{}
void AddUnitForm::on_UnitsListWidget_itemDoubleClicked(QListWidgetItem* item) {
	std::fstream stream;
	stream.open(directoryPath + item->text().toStdString(), std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	FileManager f;
	int amount;
	Unit* unit = f.readUnit(stream, amount);
	ui.UnitMorality->clear();
	ui.UnitMoralityChanges->clear();
	ui.UnitNameLineEdit->setText(QString::fromStdString(unit->getName()));
	ui.UnitMinPower->setText(QString::fromStdString(std::to_string(unit->getMinBasePower())));
	ui.UnitMaxPower->setText(QString::fromStdString(std::to_string(unit->getMaxBasePower())));
	ui.changeViability->setText(QString::fromStdString(std::to_string(unit->getViability())));
	ui.fortificationTargetCheckBox->setChecked(unit->getFortificationTarget());
	ui.renovareArmorCheckBox->setChecked(unit->getIsRenovateArmor());
	ui.UnitArmor->setText(QString::fromStdString(std::to_string(unit->getMaxArmor())));
	if (unit->getTypeID() == 1) {
		ui.UnitMorality->setText(QString::fromStdString(std::to_string(((MoralUnit*)unit)->getMorality())));
		ui.UnitMoralityChanges->setText(QString::fromStdString(std::to_string(((MoralUnit*)unit)->getMoralityChangesRate())));
	}
	ui.ChoosedUnitTargetType->setText(QString::fromStdString(uiFunctions::unitTypesToString(unit->getPriorityTargetType())));
	ui.ChoosedUnitType->setText(QString::fromStdString(uiFunctions::unitTypesToString(unit->getType())));
	int sel1 = ui.UnitTypes->currentRow();
	int sel2 = ui.UnitTargetTypes->currentRow();
	if (sel1 != -1) { // Set selected false
		ui.UnitTypes->item(sel1)->setSelected(false);
	}
	if (sel2 != -1) { // Set selected false
		ui.UnitTargetTypes->item(sel1)->setSelected(false);
	}
	ui.UnitTypes->item((int)unit->getType())->setSelected(true);
	ui.UnitTargetTypes->item((int)unit->getPriorityTargetType())->setSelected(true);
	curUnit = std::shared_ptr<Unit>(unit);
}
void AddUnitForm::on_DeleteUnitButton_clicked() {
	int cur = ui.UnitsListWidget->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose Unit!");
		return;
	}
	QString name = ui.UnitsListWidget->item(cur)->text();
	std::string fileName = directoryPath + name.toStdString();
	std::filesystem::remove(fileName);
	delete ui.UnitsListWidget->takeItem(cur);
}
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
std::shared_ptr<Unit> AddUnitForm::readUnit() {
	std::string unitName = ui.UnitNameLineEdit->text().toStdString();
	double minPower = ui.UnitMinPower->text().toDouble();
	double maxPower = ui.UnitMaxPower->text().toDouble();
	double viability = ui.changeViability->text().toDouble();
	double armor = ui.UnitArmor->text().toDouble();
	bool isRenovateArmor = ui.renovareArmorCheckBox->isChecked();
	bool fortTarget = ui.fortificationTargetCheckBox->isChecked();
	unitHelpers::unitTypes type = static_cast<unitHelpers::unitTypes>(ui.UnitTypes->currentRow());
	unitHelpers::unitTypes targetType = static_cast<unitHelpers::unitTypes>(ui.UnitTargetTypes->currentRow());
	BaseUnitBuilder* builder;
	if (ui.UnitMorality->text().isEmpty() || ui.UnitMorality->text().toDouble() == 0) {
		UnitBuilder* build = new UnitBuilder();
		build->setArmor(armor, isRenovateArmor)->setName(unitName)->setPowerAndViability(minPower, maxPower, viability)->
			setFortificationTarget(fortTarget)->setTypes(type, targetType);
		builder = build;
	}
	else {
		double morality = ui.UnitMorality->text().toDouble();
		double rate = 1;
		if (ui.UnitMoralityChanges->text().isEmpty() || ui.UnitMoralityChanges->text().toDouble() == 0) {
			rate = 1;
		}
		else {
			rate = ui.UnitMoralityChanges->text().toDouble();
		}
		MoralUnitBuilder* build = new MoralUnitBuilder();
		build->setArmor(armor, isRenovateArmor)->setName(unitName)->setPowerAndViability(minPower, maxPower, viability)->
			setFortificationTarget(fortTarget)->setTypes(type, targetType)->setMorality(morality, rate);
		builder = build;
	}
	std::shared_ptr<Unit> unit = builder->setCycling(curUnit->getCycling())->setPowerCoef(curUnit->getPowerCoef())->getResult();
	delete builder;
	return unit;
}
void AddUnitForm::on_AddUnit_clicked() {
	if (!isDataCorrect())
		return;
	std::string unitName = ui.UnitNameLineEdit->text().toStdString();
	bool isContains = false;
	for (int i = 0; i < ui.UnitsListWidget->count(); ++i)
	{
		QListWidgetItem* item = ui.UnitsListWidget->item(i);
		if (item->text().toStdString() == unitName) {
			isContains = true;
			break;
		}
	}
	bool isToAdd = true;
	if (isContains) {
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(nullptr, "Unit with such name exists.", "Do you want rewrite it?",
			QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes)
			isToAdd = true;
		else
			isToAdd = false;
	}
	bool isWrited = false;
	if (isToAdd) {
		std::vector<Item> items = curUnit->getItems();
		curUnit = readUnit();
		for (auto& item : items) {
			curUnit->addItem(item);
		}
		AddCyclingAndPowerCoefForm w(curUnit, directoryPath + unitName,isWrited);
		w.setModal(true);
		w.exec();
		if(isWrited)
			ui.UnitsListWidget->addItem(QString::fromStdString(unitName));
	}
	if (isWrited && isContains) {
		delete ui.UnitsListWidget->takeItem(ui.UnitsListWidget->count() - 1);
	}
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
void  AddUnitForm::on_ChangeItemsButton_clicked() {
	ChangeUnitItemsForm w(curUnit);
	w.setModal(true);
	w.exec();
}
void AddUnitForm::on_UnitTypes_itemClicked(QListWidgetItem* item) {
	ui.ChoosedUnitType->setText(item->text());
}
void AddUnitForm::on_UnitTargetTypes_itemClicked(QListWidgetItem* item) {
	ui.ChoosedUnitTargetType->setText(item->text());
}
