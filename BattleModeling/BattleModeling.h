#pragma once
#include<vector>
#include"Circumstance.h"
#include"Unit.h"
#include"Army.h"
#include<memory>
struct Supply {
	double army1LapSupplies = 0;
	double army2LapSupplies = 0;
	int army1SupplyLapsAmount = 0;
	int army2SupplyLapsAmount = 0;
};

class BattleModeling
{
	friend class BattleBuilder;	
private:
	Army army1;
	Army army2;
	Army army1Reinforcements;
	Army army2Reinforcements;
	double army1RoundReinforcement;
	double army2RoundReinforcement;
	Supply roundSupplies;
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

	void operator()();
};

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
};