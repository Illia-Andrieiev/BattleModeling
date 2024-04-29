#pragma once
#include<vector>
#include"Circumstance.h"
#include"Unit.h"
#include"Army.h"
#include<memory>
struct Supply {
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
	std::shared_ptr<MementoArmy> army1Memento;
	std::shared_ptr<MementoArmy> army2Memento;
	int round;///< Current battle round
	int mementoRounds; ///< Every mementoRounds make mementos
	Army army1; ///< Army 1
	Army army2; ///< Army 2
	Army army1Reinforcements; ///< Reinforcements for army 1
	Army army2Reinforcements; ///< Reinforcements for army 2
	double army1RoundReinforcement; ///< Persents of reinforcements that will add to army 1 per round
	double army2RoundReinforcement; ///< Persents of reinforcements that will add to army 1 per round
	Supply roundSupplies; ///< Round supplies for armies
	BattleModeling();
	void battleRound();
	std::vector<Circumstance> circumstances;
	Circumstance getSummCircumstance();
	void addReinforcement();
	Unit* chooseRandomUnit(Army& army, unitHelpers::unitTypes type);
public:
	static BattleModeling& getBattleModeling();
	void addCircumstance(const Circumstance& circ);
	Supply getSupplies() const;
	std::shared_ptr<MementoArmy> getArmy1Memento();
	std::shared_ptr<MementoArmy> getArmy2Memento();
	int getRound() const;
	void operator()();
};
/// Battle builder
class BattleBuilder {
	BattleModeling battle;
public:
	BattleBuilder();
	void reset() ;
	BattleModeling& getResult();
	BattleBuilder* setSupplies(const Supply& lapSupplies) ;
	BattleBuilder* setReinforcements(const Army& army1Reinforcements, const Army& army2Reinforcements,
		double  army1RoundReinforcement, double army2RoundReinforcement);
	BattleBuilder* setArmy(const Army& army1, const Army& army2);
	BattleBuilder* createMemento(int mementoRounds);
};
class BattleModelingTest {
public:
	void test();
};