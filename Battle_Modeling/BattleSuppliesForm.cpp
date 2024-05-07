#include "BattleSuppliesForm.h"
#include"UIHelpers.h"
BattleSuppliesForm::BattleSuppliesForm(BattleBuilder& builder, QWidget *parent)
	: QDialog(parent),builder(builder)
{
	ui.setupUi(this);
	setStyles();
	QRegularExpression doubl("\\d+\\.?\\d+");
	QRegularExpression intReg("\\d+");
	QValidator* validatorInt = new QRegularExpressionValidator(intReg, this);
	QValidator* validatorDoubl = new QRegularExpressionValidator(doubl, this);
	ui.Army1AmountRounds->setValidator(validatorInt);
	ui.Army1RoundSupplies->setValidator(validatorDoubl);
	ui.Army1supplies->setValidator(validatorDoubl);
	ui.Army2AmountRounds->setValidator(validatorInt);
	ui.Army2RoundSupplies->setValidator(validatorDoubl);
	ui.Army2supplies->setValidator(validatorDoubl);
	this->setFixedSize(this->size());
}

BattleSuppliesForm::~BattleSuppliesForm()
{}
void BattleSuppliesForm::on_ToMenu_clicked() {
	this->close();
}
void BattleSuppliesForm::on_ApplySupplies_clicked() {
	double startSupplies1 = ui.Army1supplies->text().isEmpty() ? 0 : ui.Army1supplies->text().toDouble();
	double startSupplies2 = ui.Army2supplies->text().isEmpty() ? 0 : ui.Army2supplies->text().toDouble();
	double suppliesPerRound1 = ui.Army1RoundSupplies->text().isEmpty() ? 0 : ui.Army1RoundSupplies->text().toDouble();
	double suppliesPerRound2 = ui.Army2RoundSupplies->text().isEmpty() ? 0 : ui.Army2RoundSupplies->text().toDouble();
	int rounds1 = ui.Army1AmountRounds->text().isEmpty() ? 0 : ui.Army1AmountRounds->text().toInt();
	int rounds2 = ui.Army2AmountRounds->text().isEmpty() ? 0 : ui.Army2AmountRounds->text().toInt();
	Supply s;
	s.army1RoundSupplies = suppliesPerRound1;
	s.army2RoundSupplies = suppliesPerRound2;
	s.army1SupplyRoundAmount = rounds1;
	s.army2SupplyRoundAmount = rounds2;
	s.army1StartSupplies = startSupplies1;
	s.army2StartSupplies = startSupplies2;
	builder.setSupplies(s);
}
void BattleSuppliesForm::setStyles() {
	ui.ApplySupplies->setStyleSheet(styles::mainButton);
	ui.ToMenu->setStyleSheet(styles::mainButton);
}