#include "BattleModeling.h"
#include <thread>
BattleModeling::BattleModeling() {}
Supply BattleModeling::getSupplies() const{
	return lapSupplies;
}
void BattleModeling::battleLap() {
	std::thread army1Thread([&]() {army1.attackArmy(army2);});
	army2.attackArmy(army1);
	army1Thread.join();
	std::cout << "army1 viability: "<<army1.countViability() << std::endl << army1.toString();
	std::cout << "army2: viability: " << army2.countViability() << std::endl << army2.toString();
}
void BattleModeling::operator()() {
	Army army1, army2, reinF1,reinF2;
	army1 = this->army1;
	army2 = this->army2;
	reinF1 = this->army1Reinforcements;
	reinF2 = this->army2Reinforcements;
	Circumstance summaryCirc = getSummCircumstance();
	army1.applyCircumstance(summaryCirc);
	army2.applyCircumstance(summaryCirc);
	army1.applyItems();
	army2.applyItems();
	army1.countViability();
	army2.countViability();
	while (army1.getViability() > 0 && army2.getViability() > 0) {
		battleLap();
		system("pause");
	}
}
Circumstance BattleModeling::getSummCircumstance() {
	std::map<unitHelpers::unitTypes, double> coef;
	for (int i = 0; i < circumstances.size(); i++) {
		for (auto& param : circumstances[i].getPowerChanges()) {
			coef[param.first] *= param.second;
		}
	}
	return Circumstance(coef, std::string("Summary"));
}
void BattleModeling::addCircumstance(const Circumstance& circ) {
	circumstances.push_back(circ);
}
BattleModeling& BattleModeling::getBattleModeling() {
	static BattleModeling battle;
	return battle;
}




BattleBuilder::BattleBuilder() {
	reset();
}
void BattleBuilder::reset() {
	battle = BattleModeling::getBattleModeling();
}
BattleModeling& BattleBuilder::getResult() {
	return battle;
}
BattleBuilder* BattleBuilder::setSupplies(const Supply& lapSupplies){
	battle.lapSupplies = lapSupplies;
	return this;
}
BattleBuilder* BattleBuilder::setReinforcements(const Army& army1Reinforcements, const Army& army2Reinforcements) {
	battle.army1Reinforcements = army1Reinforcements;
	battle.army2Reinforcements = army2Reinforcements;
	return this;
}
BattleBuilder* BattleBuilder::setArmy(const Army& army1, const Army& army2) {
	battle.army1 = army1;
	battle.army2 = army2;
	return this;
}