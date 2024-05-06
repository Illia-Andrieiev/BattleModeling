#include "ChangeBattleCircumstancesForm.h"
#include "FileManager.h"
#include"qmessagebox.h"
#include<filesystem>
#include"UIHelpers.h"
ChangeBattleCircumstancesForm::ChangeBattleCircumstancesForm(BattleModeling& battle,QWidget *parent)
	: QDialog(parent),battle(battle)
{
	QRegularExpression rx("[^/'\":;]*");
	QValidator* validator = new QRegularExpressionValidator(rx, this);
	ui.Army1Circ->setValidator(validator);
	ui.Army2Circ->setValidator(validator);
	ui.setupUi(this);
	for (auto& circ : battle.getCircumstances()) {
		ui.AppliedCircs->addItem(QString::fromStdString(circ.getName()));
	}
	ui.Army1Circ->setText(QString::fromStdString(battle.getArmy1Circumstance().getName()));
	ui.Army2Circ->setText(QString::fromStdString(battle.getArmy2Circumstance().getName()));
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator("DataBase\\Circumstances\\")) {
		ui.CircListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
	}
	setStyles();
	this->setFixedSize(this->size());
}

ChangeBattleCircumstancesForm::~ChangeBattleCircumstancesForm()
{}
void ChangeBattleCircumstancesForm::setStyles() {
	ui.ApplyCircButton->setStyleSheet(styles::mainButton);
	ui.ToMenu->setStyleSheet(styles::mainButton);
	ui.RemoveGeneralCircButton->setStyleSheet(styles::elseButtons);
	ui.ApplySpecialCircs->setStyleSheet(styles::elseButtons);
}
void ChangeBattleCircumstancesForm::on_ApplyCircButton_clicked() {
	int cur = ui.CircListWidget->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose circumstance!");
		return;
	}
	QString name = ui.CircListWidget->item(cur)->text();
	for (int i = 0; i < ui.AppliedCircs->count(); i++) {
		if (ui.AppliedCircs->item(i)->text() == name) {
			QMessageBox::information(this, "information", "Circumstance can be applied only once!");
			return;
		}
	}
	FileManager f;
	std::fstream stream;
	std::string fileName = "DataBase\\Circumstances\\" + name.toStdString();
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	Circumstance readCirc = f.readCircumstance(stream);
	stream.close();
	battle.addCircumstance(readCirc);
	ui.AppliedCircs->addItem(name);
}
void ChangeBattleCircumstancesForm::on_ToMenu_clicked() {
	this->close();
}
void ChangeBattleCircumstancesForm::on_AppliedCircs_itemDoubleClicked(QListWidgetItem* item) {
	QMessageBox::information(this, "information", QString::fromStdString(readCirc(item->text().toStdString()).toString()));
}
void ChangeBattleCircumstancesForm::on_CircListWidget_itemDoubleClicked(QListWidgetItem* item) {
	QMessageBox::information(this, "information", QString::fromStdString(readCirc(item->text().toStdString()).toString()));
}
void ChangeBattleCircumstancesForm::on_RemoveGeneralCircButton_clicked() {
	int cur = ui.AppliedCircs->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose circumstance!");
		return;
	}
	QString name = ui.AppliedCircs->item(cur)->text();
	battle.removeCircumstance(name.toStdString());
	delete ui.AppliedCircs->takeItem(cur);
}
void ChangeBattleCircumstancesForm::on_ApplySpecialCircs_clicked() {
	QString circ1 = ui.Army1Circ->text();
	QString circ2 = ui.Army2Circ->text();
	if (!isCircExist(circ1) && !circ1.isEmpty()) {
		QMessageBox::warning(this, "warning", "Entered circumstance for army 1 do not exist!");
		return;
	}
	if (!isCircExist(circ2) && !circ2.isEmpty()) {
		QMessageBox::warning(this, "warning", "Entered circumstance for army 2 do not exist!");
		return;
	}
	if (circ1.isEmpty()) {
		battle.setArmy1SpecialCircumstance(Circumstance());
	}
	else {
		battle.setArmy1SpecialCircumstance(readCirc(circ1.toStdString()));
	}
	if (circ2.isEmpty()) {
		battle.setArmy2SpecialCircumstance(Circumstance());
	}
	else {
		battle.setArmy2SpecialCircumstance(readCirc(circ2.toStdString()));
	}
}
bool ChangeBattleCircumstancesForm::isCircExist(QString name) {
	for (int i = 0; i < ui.CircListWidget->count(); i++) {
		if (ui.CircListWidget->item(i)->text() == name) {
			return true;
		}
	}
	return false;
}
Circumstance ChangeBattleCircumstancesForm::readCirc(std::string name){
	FileManager f;
	std::fstream stream;
	std::string fileName = "DataBase\\Circumstances\\" + name;
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	Circumstance readCirc = f.readCircumstance(stream);
	stream.close();
	return readCirc;
}