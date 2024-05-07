#include "BattleModeling.h"
#include"MoralUnit.h"
#include"FileManager.h"
#include <thread>
#include<random>
#include<filesystem>
///Constructor
BattleModeling::BattleModeling() {
	army1RoundReinforcement = 100;
	army2RoundReinforcement = 100;
	round = 0;
	mementoRounds = 0;
	army1ViabiliryToLoose = 0;
	army2ViabiliryToLoose = 0;
}
std::vector<std::shared_ptr<MementoArmy>> BattleModeling::getArmy1Mementoes() {
	return army1Mementoes;
}
std::vector<std::shared_ptr<MementoArmy>> BattleModeling::getArmy2Mementoes() {
	return army2Mementoes;
}
/// Return armies supplies
Supply BattleModeling::getSupplies() const {
	return roundSupplies;
}
void BattleModeling::setArmy1SpecialCircumstance(const Circumstance& circ) {
	army1SpecialCirc = circ;
}
void BattleModeling::setArmy2SpecialCircumstance(const Circumstance& circ) {
	army2SpecialCirc = circ;
}
/// One battle round
void BattleModeling::battleRound() {
	round++;
	manageSupplies();
	///< Attack army
	std::thread army1Thread([&]() {army1.attackArmy(army2); });
	army2.attackArmy(army1);
	army1Thread.join();
	///< Count viability
	double viability1 = 0, viability2 = 0;
	std::thread th1([&]() {viability1 = army1.countViability(); });
	std::thread th2([&]() {viability2 = army2.countViability(); });
	///< Count power
	std::thread th3([&]() {army1.countPower(); });
	army2.countPower();
	th1.join();
	th2.join();
	th3.join();
	///< Print armies
	std::fstream log;
	log.open("log", std::ios::app | std::ios::in | std::ios::out);
	log << "army1 viability: " << viability1 << std::endl << army1.toString() << std::endl;
	log << "army2: viability: " << viability2 << std::endl << army2.toString() << std::endl;
	log.close();
}
void BattleModeling::manageSupplies() {
	if (roundSupplies.army1SupplyRoundAmount >= round) {
		army1.changeSupplies(roundSupplies.army1RoundSupplies);
	}
	if (roundSupplies.army2SupplyRoundAmount >= round) {
		army2.changeSupplies(roundSupplies.army2RoundSupplies);
	}
}
/// Main Battle modeling method 
std::vector<std::pair<double, double>> BattleModeling::operator()() {
	round = 0;
	resultPoints.clear();
	Army army1, army2, reinf1, reinf2;
	this->army1.changeSupplies(-this->army1.getSupplies());
	this->army1.changeSupplies(roundSupplies.army1StartSupplies);
	this->army2.changeSupplies(-this->army2.getSupplies());
	this->army2.changeSupplies(roundSupplies.army2StartSupplies);
	army1 = this->army1;
	army2 = this->army2;
	reinf1 = this->army1Reinforcements;
	reinf2 = this->army2Reinforcements;
	prepareForBattle();
	while (this->army1.getViability() > army1ViabiliryToLoose && this->army2.getViability() > army2ViabiliryToLoose
		&&(this->army1.getSupplies()>0 || this->army2.getSupplies() > 0)) {
		if (mementoRounds != 0) { ///< Create mementos
			if (round % mementoRounds == 0) {
				army1Mementoes.push_back( army1.createMemento(round));	
				army2Mementoes.push_back(army2.createMemento(round));
			}
		}
		resultPoints.push_back(std::pair<double, double>(this->army1.getViability(), this->army2.getViability()));
		battleRound();
		addReinforcement(); ///< Add reinforcement
		//system("pause");
	}
	resultPoints.push_back(std::pair<double, double>(this->army1.getViability(), this->army2.getViability()));
	this->army1 = army1;
	this->army2 = army2;
	this->army1Reinforcements = reinf1;
	this->army2Reinforcements = reinf2;
	return resultPoints;
}
/// Preparetion for battle
void BattleModeling::prepareForBattle() {
	Circumstance summaryCirc = getSummCircumstance();
	///< Apply circumstances for armies
	std::thread th1([&]() {this->army1.applyCircumstance(summaryCirc); });
	std::thread th2([&]() {this->army1Reinforcements.applyCircumstance(summaryCirc); });
	std::thread th3([&]() {this->army2Reinforcements.applyCircumstance(summaryCirc); });
	this->army2.applyCircumstance(summaryCirc);
	th1.join();
	th2.join();
	th3.join();
	th1 = std::thread([&]() {this->army1.applyCircumstance(army1SpecialCirc); });
	th2 = std::thread([&]() {this->army1Reinforcements.applyCircumstance(army1SpecialCirc); });
	th3 = std::thread([&]() {this->army2Reinforcements.applyCircumstance(army2SpecialCirc); });
	this->army2.applyCircumstance(army2SpecialCirc);
	th1.join();
	th2.join();
	th3.join();
	///Apply items
	th1 = std::thread([&]() {this->army1.applyItems(); });
	th2 = std::thread([&]() {this->army1Reinforcements.applyItems(); });
	th3 = std::thread([&]() {this->army2Reinforcements.applyItems(); });
	this->army2.applyItems();
	th1.join();
	th2.join();
	th3.join();
	th1 = std::thread([&]() {this->army1.countViability(); });
	this->army2.countViability();
	th1.join();
	std::filesystem::remove("log");
}
std::vector<Circumstance> BattleModeling::getCircumstances() const {
	return circumstances;
}
Circumstance BattleModeling::getArmy1Circumstance() const {
	return army1SpecialCirc;
}
Circumstance BattleModeling::getArmy2Circumstance() const {
	return army2SpecialCirc;
}
/// Return equivalent circumstance for all
Circumstance BattleModeling::getSummCircumstance() {
	std::map<unitHelpers::unitTypes, double> coef;
	for (int i = 0; i < circumstances.size(); i++) {
		for (auto& param : circumstances[i].getPowerChanges()) {
			coef[param.first] *= param.second;
		}
	}
	return Circumstance(coef, std::string("Summary"));
}
/// Remove circumstance with that name
void BattleModeling::removeCircumstance(std::string name) {
	for (int i = 0; i < circumstances.size(); i++) {
		if (circumstances[i].getName() == name) {
			std::swap(circumstances[i], circumstances[circumstances.size() - 1]);
			circumstances.pop_back();
		}
	}
}
/// Add circumstance
void BattleModeling::addCircumstance(const Circumstance& circ) {
	circumstances.push_back(circ);
}
/// Return battle modeling
BattleModeling& BattleModeling::getBattleModeling() {
	static BattleModeling battle;
	return battle;
}
/// Choose random unit with this type from army. Return nullptr if all units add, or type not exist in army
Unit* BattleModeling::chooseRandomUnit(Army& army, unitHelpers::unitTypes type) {
	try {
		int posType = army1.unitTypesPositions.at(type);
		if (army.positionOfFirstAlive[posType] == -1)
			return nullptr;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(army.positionOfFirstAlive[posType], (int)army.units[posType].size() - 1);
		int pos = distr(gen);
		Unit* resUnit = army.units[posType][pos]->clone();
		std::swap(army.units[posType][pos], army.units[posType][army.positionOfFirstAlive[posType]]);///< Swap last added unit to start. 
		++army.positionOfFirstAlive[posType];///< Position of first alive represent new first to add
		if (army.positionOfFirstAlive[posType] == army.units[posType].size()) {
			army.positionOfFirstAlive[posType] = -1;
		}
		return resUnit;
	}
	catch (const std::out_of_range&) {
		return nullptr;
	}
}
/// Add reinforcements for armies
void BattleModeling::addReinforcement() {
	if (army1.getViability() == 0 || army2.getViability() == 0) { ///< If army dead -> return
		return;
	}
	for (int i = 0; i < army1Reinforcements.units.size(); i++) { ///< For every type
		int amountReinf = (int)(army1Reinforcements.units[i].size() * army1RoundReinforcement / 100); ///< How many units will add 
		while (amountReinf > 0) {
			--amountReinf;
			Unit* reinfUnit = chooseRandomUnit(army1Reinforcements, army1Reinforcements.units[i][0]->getType()); ///< Choose unit to add
			if (reinfUnit == nullptr)
				break;
			army1.addUnit(*reinfUnit, 1);
			delete reinfUnit;
		}
	}
	for (int i = 0; i < army2Reinforcements.units.size(); i++) { ///< For every type
		int amountReinf = (int)(army2Reinforcements.units[i].size() * army2RoundReinforcement / 100); ///< How many units will add 
		while (amountReinf > 0) {
			--amountReinf;
			Unit* reinfUnit = chooseRandomUnit(army2Reinforcements, army2Reinforcements.units[i][0]->getType()); ///< Choose unit to add
			if (reinfUnit == nullptr)
				break;
			army2.addUnit(*reinfUnit, 1);
			delete reinfUnit;
		}
	}
}
int BattleModeling::getRound() const {
	return round;
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
BattleBuilder* BattleBuilder::setSupplies(const Supply& lapSupplies) {
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
BattleBuilder* BattleBuilder::createMemento(int mementoRounds) {
	battle.mementoRounds = mementoRounds;
	return this;
}
BattleBuilder* BattleBuilder::setLoosePoints(double army1ViabilityToLoose, double army2ViabilityToLoose) {
	battle.army1ViabiliryToLoose = army1ViabilityToLoose;
	battle.army2ViabiliryToLoose = army2ViabilityToLoose;
	return this;
}
void BattleModelingTest::test() {
	AttackArmyTest t1;
	UnitTest t2;
	MoralUnitTest t3;
	FileManagerTest t4;
	ArmyTest t5;
	t1.test();
	t2.test();
	t3.test();
	t4.test();
	t5.test();
}