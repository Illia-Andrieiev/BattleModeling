#include "AddItemForm.h"
#include"FileManager.h"
#include<qregularexpression.h>
#include<qmessagebox.h>
#include<filesystem>
#include "UIHelpers.h"
AddItemForm::AddItemForm(QWidget* parent)
	: QDialog(parent)
{
	directoryPath = "DataBase\\Items\\";
	ui.setupUi(this);
	ui.ItemNameLineEdit->setMaxLength(256);
	QRegularExpression rx("[^/'\":;]*");
	QRegularExpression pos("\\d+\\.?\\d+");
	QRegularExpression all("\\-?\\d+\\.?\\d+");
	QValidator* validatorName = new QRegularExpressionValidator(rx, this);
	ui.ItemNameLineEdit->setValidator(validatorName);
	QValidator* ValidatorDoubleAll = new QRegularExpressionValidator(all, this);
	QValidator* ValidatorDoublePositive = new QRegularExpressionValidator(pos, this);
	ui.ItemPower->setValidator(ValidatorDoubleAll);
	ui.changeViability->setValidator(ValidatorDoubleAll);
	ui.PowerCoef->setValidator(ValidatorDoublePositive);
	uiFunctions::fillTypes(ui.UnitTypes);
	fillItemsList();
	this->setFixedSize(this->size());
	setStyles();
}
void AddItemForm::on_UnitTypes_itemDoubleClicked(QListWidgetItem* item) {
	int pos = ui.UnitTypes->row(item);
	if (pos == -1)
		return;
	else {
		try {
			double coef = curItem.getPowerChanges().at(static_cast<unitHelpers::unitTypes>(pos));
			ui.PowerCoef->setText(QString::fromStdString(std::to_string(coef)));
		}
		catch (const std::out_of_range&) {
			ui.PowerCoef->setText(QString::fromStdString(std::to_string(1)));
		}
		
	}
}
AddItemForm::~AddItemForm()
{
}
void AddItemForm::on_ToMenu_clicked() {
	this->close();
}
void AddItemForm::on_AddItemButton_clicked() {
	std::string itemName = ui.ItemNameLineEdit->text().toStdString();
	if (itemName.empty()) {
		QMessageBox::warning(this, "warning", "Enter item name!");
		return;
	}
	curItem.setName(itemName);
	bool isContains = false;
	for (int i = 0; i <ui.ItemsListWidget->count(); ++i)
	{
		QListWidgetItem* item = ui.ItemsListWidget->item(i);
		if (item->text().toStdString() == itemName) {
			isContains = true;
			break;
		}
	}
	bool isToAdd = true;
	if (isContains) {
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(nullptr, "Item with such name exists.", "Do you want rewrite it?",
			QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes)
			isToAdd = true;
		else
			isToAdd = false;
	}
	if (isToAdd) {
		writeCurItem();
	}
	else { return; }
}
void AddItemForm::on_DeleteItemButton_clicked() {
	int cur = ui.ItemsListWidget->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose Circumstance!");
		return;
	}
	QString name = ui.ItemsListWidget->item(cur)->text();
	std::string fileName = directoryPath + name.toStdString();
	std::filesystem::remove(fileName);
	delete ui.ItemsListWidget->takeItem(cur);
}
void AddItemForm::writeCurItem() {
	std::string fileName = directoryPath + curItem.getName();
	std::filesystem::remove(fileName);
	double powerChanges = std::stod(ui.ItemPower->text().toStdString());
	double viabilityChanges = std::stod(ui.changeViability->text().toStdString());
	curItem.setViabilityChanges(viabilityChanges);
	curItem.setBasePowerChanges(powerChanges);
	std::fstream stream;
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	FileManager f;
	f.writeItem(curItem, stream);
	stream.close();
	ui.ItemsListWidget->addItem(QString::fromStdString(curItem.getName()));
}
void AddItemForm::on_AddPowerCoef_clicked() {
	int cur = ui.UnitTypes->currentRow();
	if ( cur ==-1) {
		QMessageBox::warning(this, "warning", "Choose unit type!");
		return;
	}
	curItem.setPowerCoef(std::pair<unitHelpers::unitTypes, double>
		(static_cast<unitHelpers::unitTypes>(cur),
			std::stod(ui.PowerCoef->text().toStdString())));
}
void AddItemForm::on_ItemsListWidget_itemDoubleClicked(QListWidgetItem* item) {
	std::string itemName = item->text().toStdString();
	std::string fileName = directoryPath + itemName;
	std::fstream stream;
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	FileManager f;
	Item readItem = f.readItem(stream);
	stream.close();
	curItem = readItem;
	ui.changeViability->setText(QString::fromStdString(std::to_string(readItem.getViabilityChanges())));
	ui.ItemPower->setText(QString::fromStdString(std::to_string(readItem.getBasePowerChanges())));
	ui.ItemNameLineEdit->setText(QString::fromStdString(curItem.getName()));
}
void AddItemForm::fillItemsList() {
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(directoryPath)) {
		ui.ItemsListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
	}
}

void AddItemForm::setStyles() {
	ui.AddItemButton->setStyleSheet(styles::mainButton);
	ui.ToMenu->setStyleSheet(styles::mainButton);
	ui.AddPowerCoef->setStyleSheet(styles::elseButtons);
	ui.DeleteItemButton->setStyleSheet(styles::elseButtons);
}