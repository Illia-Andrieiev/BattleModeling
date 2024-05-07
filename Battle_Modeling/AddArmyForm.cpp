#include "AddArmyForm.h"
#include"FileManager.h"
#include<qmessagebox.h>
#include<filesystem>
#include"UIHelpers.h"
AddArmyForm::AddArmyForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setStyles();
	fillArmyUnits();
	ui.ArmyNameLineEdit->setMaxLength(256);
	QRegularExpression rx("[^/'\":;]*");
	QValidator* validatorName = new QRegularExpressionValidator(rx, this);
	ui.ArmyNameLineEdit->setValidator(validatorName);
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator("DataBase\\Units\\")) {
		ui.UnitsListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
	}
	for (const auto& entry : fs::directory_iterator("DataBase\\Armies\\")) {
		ui.ArmiesListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
	}
	this->setFixedSize(this->size());
}
AddArmyForm::AddArmyForm(QString armyName, QWidget* parent) {
	ui.setupUi(this);
	setStyles();
	fillArmyUnits();
	QRegularExpression rx("[^/'\":;]*");
	QValidator* validatorName = new QRegularExpressionValidator(rx, this);
	ui.ArmyNameLineEdit->setValidator(validatorName);
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator("DataBase\\Units\\")) {
		ui.UnitsListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
	}
	for (const auto& entry : fs::directory_iterator("DataBase\\Armies\\")) {
		ui.ArmiesListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
	}
	this->setFixedSize(this->size());
	std::string fileName = "DataBase\\Armies\\" + armyName.toStdString();
	FileManager f;
	curArmy = f.readArmy(fileName);
	while (ui.ArmyUnitsTable->rowCount() > 0)
		ui.ArmyUnitsTable->removeRow(0);
	fillArmyUnits();
	ui.ArmyNameLineEdit->setText(QString::fromStdString(curArmy.getName()));
	ui.fortification->setText(QString::fromStdString(curArmy.getFortification().getName()));
}
void AddArmyForm::on_ToMenu_clicked() {
	this->close();
}
AddArmyForm::~AddArmyForm()
{}
void AddArmyForm::on_ArmiesListWidget_itemDoubleClicked(QListWidgetItem* item) {
	std::string itemName = item->text().toStdString();
	std::string fileName = "DataBase\\Armies\\" + itemName;
	FileManager f;
	curArmy = f.readArmy(fileName);
	while (ui.ArmyUnitsTable->rowCount() > 0)
		ui.ArmyUnitsTable->removeRow(0);
	fillArmyUnits();
	ui.ArmyNameLineEdit->setText(QString::fromStdString(curArmy.getName()));
	ui.fortification->setText(QString::fromStdString(curArmy.getFortification().getName()));
}
void AddArmyForm::on_UnitsListWidget_itemDoubleClicked(QListWidgetItem* item) {
	FileManager f;
	std::fstream stream;
	std::string fileName = "DataBase\\Units\\" + item->text().toStdString();
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	int amount=0;
	Unit* readUnit = f.readUnit(stream,amount);
	stream.close();
	QMessageBox::information(this, "information", QString::fromStdString(readUnit->toString()));
	delete readUnit;
	
}
void AddArmyForm::on_AddUnitButton_clicked() {
	int cur = ui.UnitsListWidget->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose unit!");
		return;
	}
	QString name = ui.UnitsListWidget->item(cur)->text();
	FileManager f;
	std::fstream stream;
	std::string fileName = "DataBase\\Units\\" + name.toStdString();
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	int amount;
	Unit* readUnit = f.readUnit(stream,amount);
	stream.close();
	bool ok;
	amount = QInputDialog::getInt(0, "How many units add?", "", 0, 0, 2000000, 1, &ok);
	if (amount == 0)
		return;
	curArmy.addUnit(*readUnit,amount);
	ui.ArmyUnitsTable->insertRow(ui.ArmyUnitsTable->rowCount());
	ui.ArmyUnitsTable->setItem(ui.ArmyUnitsTable->rowCount() - 1,
		0, new QTableWidgetItem(QString::fromStdString(readUnit->getName())));
	ui.ArmyUnitsTable->setItem(ui.ArmyUnitsTable->rowCount() - 1,
		1, new QTableWidgetItem(QString::number(amount)));
}
void AddArmyForm::on_AddArmyButton_clicked() {
	std::string armyName = ui.ArmyNameLineEdit->text().toStdString();
	if (armyName.empty()) {
		QMessageBox::warning(this, "warning", "Enter army name!");
		return;
	}
	curArmy.setName(armyName);
	bool isContains = false;
	for (int i = 0; i < ui.ArmiesListWidget->count(); ++i)
	{
		QListWidgetItem* item = ui.ArmiesListWidget->item(i);
		if (item->text().toStdString() == armyName) {
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
		writeCurArmy();
		if (isContains)
			delete ui.ArmiesListWidget->takeItem(ui.ArmiesListWidget->count() - 1);
	}
} 

void AddArmyForm::on_AddFortificationButton_clicked() {
	int cur = ui.UnitsListWidget->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose unit to set as fortification!");
		return;
	}
	QString name = ui.UnitsListWidget->item(cur)->text();
	FileManager f;
	std::fstream stream;
	std::string fileName = "DataBase\\Units\\" + name.toStdString();
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	int amount;
	Unit* readUnit = f.readUnit(stream, amount);
	stream.close();
	curArmy.setFortification(*readUnit);
	ui.fortification->setText(QString::fromStdString(readUnit->getName()));
}
void AddArmyForm::writeCurArmy() {
	std::string fileName = "DataBase\\Armies\\" + curArmy.getName();
	std::filesystem::remove(fileName);
	FileManager f;
	f.writeArmy(curArmy, fileName);
	ui.ArmiesListWidget->addItem(QString::fromStdString(curArmy.getName()));
}
void AddArmyForm::fillArmyUnits() {
	Iterator* iter = curArmy.createSequentiallyTypeIterator();
	int amount = 1;
	if (!iter->hasMore()) {
		delete iter;
		return;
	}
	Unit* prev = iter->getNext();
	while (iter->hasMore()) {
		Unit* cur = iter->getNext();
		if (cur->isEqual(prev)) {
			amount++;
		}
		else {
			ui.ArmyUnitsTable->insertRow(ui.ArmyUnitsTable->rowCount());
			ui.ArmyUnitsTable->setItem(ui.ArmyUnitsTable->rowCount() - 1,
				0, new QTableWidgetItem(QString::fromStdString(prev->getName())));
			ui.ArmyUnitsTable->setItem(ui.ArmyUnitsTable->rowCount() - 1,
				1, new QTableWidgetItem(QString::number(amount)));	
			prev = cur;
			amount = 1;
		}
	}
	ui.ArmyUnitsTable->insertRow(ui.ArmyUnitsTable->rowCount());
	ui.ArmyUnitsTable->setItem(ui.ArmyUnitsTable->rowCount() - 1,
		0, new QTableWidgetItem(QString::fromStdString(prev->getName())));
	ui.ArmyUnitsTable->setItem(ui.ArmyUnitsTable->rowCount() - 1,
		1, new QTableWidgetItem(QString::number(amount)));
	delete iter;
}
void AddArmyForm::setStyles() {
	ui.AddArmyButton->setStyleSheet(styles::mainButton);
	ui.AddUnitButton->setStyleSheet(styles::elseButtons);
	ui.ToMenu->setStyleSheet(styles::mainButton);
	ui.AddFortificationButton->setStyleSheet(styles::elseButtons);
	ui.DeleteArmyButton->setStyleSheet(styles::elseButtons);
	ui.DeleteFortificationButton->setStyleSheet(styles::elseButtons);
	ui.DeleteUnitButton->setStyleSheet(styles::elseButtons);
}
void AddArmyForm::on_DeleteUnitButton_clicked() {
	int cur = ui.ArmyUnitsTable->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose unit to delete!");
		return;
	}
	QString unitName = ui.ArmyUnitsTable->item(cur, 0)->text();
	while(curArmy.deleteUnit(unitName.toStdString())){}
	ui.ArmyUnitsTable->removeRow(cur);
	ui.ArmyUnitsTable->clearSelection();
}
void AddArmyForm::on_DeleteFortificationButton_clicked() {
	Unit u;
	curArmy.setFortification(u);
	ui.fortification->setText("default");
}
void AddArmyForm::on_DeleteArmyButton_clicked() {
	int cur = ui.ArmiesListWidget->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose army!");
		return;
	}
	QString name = ui.ArmiesListWidget->item(cur)->text();
	std::string fileName = "DataBase\\Armies\\" + name.toStdString();
	std::filesystem::remove(fileName);
	delete ui.ArmiesListWidget->takeItem(cur);
}