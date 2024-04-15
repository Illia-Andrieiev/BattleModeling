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
protected:
	
private:
	Army army1;
	Army army2;
	Army army1Reinforcements;
	Army army2Reinforcements;
	Supply lapSupplies;
	BattleModeling();
	void battleLap();
	std::vector<ModernCircumstance> circumstances;
	ModernCircumstance getSummCircumstance();
public:
	static BattleModeling& getBattleModeling();
	void addCircumstance(const ModernCircumstance& circ);
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
	BattleBuilder* setReinforcements(const Army& army1Reinforcements, const Army& army2Reinforcements);
	BattleBuilder* setArmy(const Army& army1, const Army& army2);
};