#include "BattleModeling.h"
#include <thread>
#include<random>
BattleModeling::BattleModeling() {
	army1RoundReinforcement = 100;
	army2RoundReinforcement = 100;
}
Supply BattleModeling::getSupplies() const{
	return roundSupplies;
}
void BattleModeling::battleRound() {
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
	std::cout << "army1 viability: "<< viability1 << std::endl << army1.toString()<<std::endl;
	//std::cout << "army2: viability: " << viability2 << std::endl << army2.toString()<<std::endl;
	addReinforcement();
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
		battleRound();
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

Unit* BattleModeling::chooseRandomUnit(Army& army, unitHelpers::unitTypes type) {
	try {
		int posType = army1.unitTypesPositions.at(type);
		if (army.positionOfFirstAlive[posType] == -1)
			return nullptr;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(army.positionOfFirstAlive[posType], (int)army.units[posType].size()-1);
		int pos = distr(gen);
		Unit* resUnit = army.units[posType][pos]->clone();
		std::swap(army.units[posType][pos], army.units[posType][army.positionOfFirstAlive[posType]]);
		++army.positionOfFirstAlive[posType];
		if (army.positionOfFirstAlive[posType] == army.units[posType].size()) {
			army.positionOfFirstAlive[posType] = -1;
		}
		return resUnit;
	}
	catch (const std::out_of_range&) {
		return nullptr;
	}
}
void BattleModeling::addReinforcement() {
	if (army1.getViability() == 0 || army2.getViability() == 0) {
		return;
	}
	for (int i = 0; i < army1Reinforcements.units.size(); i++) {
		int amountReinf = (int)(army1Reinforcements.units[i].size() * army1RoundReinforcement/100);
		while (amountReinf > 0) {
			--amountReinf;
			Unit* reinfUnit = chooseRandomUnit(army1Reinforcements, army1Reinforcements.units[i][0]->getType());
			if (reinfUnit == nullptr)
				break;
			army1.addUnit(*reinfUnit,1);
			delete reinfUnit;
		}
	}
	for (int i = 0; i < army2Reinforcements.units.size(); i++) {
		int amountReinf = (int)(army2Reinforcements.units[i].size() * army2RoundReinforcement / 100);
		while (amountReinf > 0) {
			--amountReinf;
			Unit* reinfUnit = chooseRandomUnit(army2Reinforcements, army2Reinforcements.units[i][0]->getType());
			if (reinfUnit == nullptr)
				break;
			army2.addUnit(*reinfUnit, 1);
			delete reinfUnit;
		}
	}
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
	battle.roundSupplies = lapSupplies;
	return this;
}
BattleBuilder* BattleBuilder::setReinforcements(const Army& army1Reinforcements, const Army& army2Reinforcements,
	double  army1RoundReinforcement, double army2RoundReinforcement) {
	if (army1RoundReinforcement <= 0) {
		army1RoundReinforcement = 1;
	}
	if (army2RoundReinforcement <= 0) {
		army2RoundReinforcement = 1;
	}
	battle.army1RoundReinforcement = army1RoundReinforcement;
	battle.army2RoundReinforcement = army2RoundReinforcement;
	battle.army1Reinforcements = army1Reinforcements;
	battle.army2Reinforcements = army2Reinforcements;
	return this;
}
BattleBuilder* BattleBuilder::setArmy(const Army& army1, const Army& army2) {
	battle.army1 = army1;
	battle.army2 = army2;
	return this;
}