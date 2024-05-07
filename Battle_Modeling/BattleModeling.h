#pragma once
#include<vector>
#include"Circumstance.h"
#include"Unit.h"
#include"Army.h"
#include<memory>
/// Supplies paramenters for armies
struct Supply {
	double army1StartSupplies = 0; ///< Army1 start supplies
	double army2StartSupplies = 0; ///< Army1 start supplies
	double army1RoundSupplies = 0; ///< Round supplies for army1 
	double army2RoundSupplies = 0; ///< Round supplies for army2 
	int army1SupplyRoundAmount = 0; ///< How many rounds supplies will add for army1
	int army2SupplyRoundAmount = 0; ///< How many rounds supplies will add for army2
};
/// Class that represents battle modeling
class BattleModeling
{
	friend class BattleBuilder;
private:
	std::vector<std::shared_ptr<MementoArmy>> army1Mementoes;
	std::vector<std::shared_ptr<MementoArmy>> army2Mementoes;
	int round;///< Current battle round
	int mementoRounds; ///< Every mementoRounds make mementos
	std::vector<std::pair<double, double>> resultPoints; ///< Pairs <army1 viability, army2 viability> for every battle round
	Army army1; ///< Army 1
	Army army2; ///< Army 2
	double army1ViabiliryToLoose; ///< After army1 viability reach this point, then it loose
	double army2ViabiliryToLoose; ///< After army2 viability reach this point, then it loose
	Army army1Reinforcements; ///< Reinforcements for army 1
	Army army2Reinforcements; ///< Reinforcements for army 2
	double army1RoundReinforcement; ///< Persents of reinforcements that will add to army 1 per round
	double army2RoundReinforcement; ///< Persents of reinforcements that will add to army 2 per round
	Supply roundSupplies; ///< Round supplies for armies
	BattleModeling();
	void battleRound();
	std::vector<Circumstance> circumstances;
	Circumstance army1SpecialCirc;
	Circumstance army2SpecialCirc;
	Circumstance getSummCircumstance();
	void addReinforcement();
	void prepareForBattle();
	Unit* chooseRandomUnit(Army& army, unitHelpers::unitTypes type);
	void manageSupplies();
public:
	static BattleModeling& getBattleModeling();
	void addCircumstance(const Circumstance& circ);
	void setArmy1SpecialCircumstance(const Circumstance& circ);
	void setArmy2SpecialCircumstance(const Circumstance& circ);
	Supply getSupplies() const;
	std::vector<Circumstance> getCircumstances() const;
	Circumstance getArmy1Circumstance() const;
	Circumstance getArmy2Circumstance() const;
	void removeCircumstance(std::string name);
	std::vector<std::shared_ptr<MementoArmy>> getArmy1Mementoes();
	std::vector<std::shared_ptr<MementoArmy>> getArmy2Mementoes();
	int getRound() const;
	std::vector<std::pair<double,double>> operator()();
};
/// Battle builder
class BattleBuilder {
	BattleModeling battle;
public:
	BattleBuilder();
	void reset();
	BattleModeling& getResult();
	BattleBuilder* setSupplies(const Supply& lapSupplies);
	BattleBuilder* setReinforcements(const Army& army1Reinforcements, const Army& army2Reinforcements,
		double  army1RoundReinforcement, double army2RoundReinforcement);
	BattleBuilder* setArmy(const Army& army1, const Army& army2);
	BattleBuilder* createMemento(int mementoRounds);
	BattleBuilder* setLoosePoints(double army1ViabilityToLoose, double army2ViabilityToLoose);
};
class BattleModelingTest {
public:
	void test();
};