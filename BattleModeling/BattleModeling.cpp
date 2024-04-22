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
	double viability1=0, viability2=0;
	std::thread th1([&]() {viability1 = army1.countViability(); });
	std::thread th2([&]() {viability2 = army2.countViability(); });
	std::thread th3([&]() {army1.countPower(); });
	army2.countPower();
	th1.join();
	th2.join();
	th3.join();
	std::cout << "army1 viability: "<< viability1 << std::endl << army1.toString();
	std::cout << "army2: viability: " << viability2 << std::endl << army2.toString();

}
void BattleModeling::operator()() {
	Army army1, army2, reinF1,reinF2;
	army1 = this->army1;
	army2 = this->army2;
	reinF1 = this->army1Reinforcements;
	reinF2 = this->army2Reinforcements;
	Circumstance summaryCirc = getSummCircumstance();
	std::thread th1([&]() {army1.applyCircumstance(summaryCirc); });
	army2.applyCircumstance(summaryCirc);
	th1.join();
	th1 = std::thread([&]() {army1.applyItems(); });
	army2.applyItems();
	th1.join();
	th1 = std::thread([&]() {this->army1.countViability(); });
	this->army2.countViability();
	th1.join();
	while (this->army1.getViability() > 0 && this->army2.getViability() > 0) {
		battleLap();
//		system("pause");
	}
	this->army1 = army1;
	this->army2 = army2;
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