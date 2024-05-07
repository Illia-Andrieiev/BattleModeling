#include "ChangeBattleReinforcementsForm.h"
#include"AddArmyForm.h"
#include"UIHelpers.h"
#include"FileManager.h"
ChangeBattleReinforcementsForm::ChangeBattleReinforcementsForm(BattleBuilder& builder, QWidget *parent)
	: QDialog(parent),builder(builder)
{
	ui.setupUi(this);
	QRegularExpression rx("[^/'\":;]*");
	QRegularExpression doubl("\\d+\\.?\\d+");
	QValidator* validator = new QRegularExpressionValidator(rx, this);
	QValidator* validatorDoubl = new QRegularExpressionValidator(doubl, this);
	ui.Army1Reinf->setValidator(validator);
	ui.Army2Reinf->setValidator(validator);
	ui.Army1Reinf->setMaxLength(256);
	ui.Army2Reinf->setMaxLength(256);
	ui.Army1Percents->setValidator(validatorDoubl);
	ui.Army2Percents->setValidator(validatorDoubl);
	setStyles();
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator("DataBase\\Armies\\")) {
		ui.ArmiesListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
	}
	this->setFixedSize(this->size());
}

ChangeBattleReinforcementsForm::~ChangeBattleReinforcementsForm()
{}
void ChangeBattleReinforcementsForm::on_ApplyReinf_clicked() {
	QString army1Reinf = ui.Army1Reinf->text();
	QString army1Persents = ui.Army1Percents->text();
	Army army1Reinforcement;
	Army army2Reinforcement;
	FileManager f;
	if (army1Reinf.isEmpty() && army1Persents.isEmpty()) {
		QMessageBox::warning(this, "warning", "Enter how much persents of reinforcements\n will add to army 1 every round!");
		return;
	}
	if (!army1Reinf.isEmpty()) {
		if (isReinfExist(army1Reinf)) {
			QMessageBox::warning(this, "warning", "Army 1 with entered name do not exist!");
			return;
		}
		std::string fileName = "DataBase\\Armies\\" + army1Reinf.toStdString();
		army1Reinforcement = f.readArmy(fileName);
	}
	QString army2Reinf = ui.Army2Reinf->text();
	QString army2Persents = ui.Army2Percents->text();
	if (army2Reinf.isEmpty() && army2Persents.isEmpty()) {
		QMessageBox::warning(this, "warning", "Enter how much persents of reinforcements\n will add to army 2 every round!");
		return;
	}
	if (!army2Reinf.isEmpty()) {
		if(isReinfExist(army2Reinf)){
			QMessageBox::warning(this, "warning", "Army 2 with entered name do not exist!");
			return;
		}
		std::string fileName = "DataBase\\Armies\\" + army2Reinf.toStdString();
		army2Reinforcement = f.readArmy(fileName);
	}
	QString p1 = ui.Army1Percents->text();
	QString p2 = ui.Army2Percents->text();
	double persent1 = p1.isEmpty() ? 0 : p1.toDouble();
	double persent2 = p2.isEmpty() ? 0 : p2.toDouble();
	builder.setReinforcements(army1Reinforcement, army2Reinforcement, persent1, persent2);
}
void ChangeBattleReinforcementsForm::on_ToMenu_clicked() {
	this->close();
}
void ChangeBattleReinforcementsForm::on_ArmiesListWidget_itemDoubleClicked(QListWidgetItem* item) {
	AddArmyForm w(item->text());
	w.setModal(true);
	w.exec();
}
void ChangeBattleReinforcementsForm::setStyles() {
	ui.ApplyReinf->setStyleSheet(styles::mainButton);
	ui.ToMenu->setStyleSheet(styles::mainButton);
}
bool ChangeBattleReinforcementsForm::isReinfExist(QString name) {
	for (int i = 0; i < ui.ArmiesListWidget->count(); i++) {
		if (ui.ArmiesListWidget->item(i)->text() == name) {
			return true;
		}
	}
	return false;
}