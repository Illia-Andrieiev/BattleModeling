#pragma once
#include<vector>
#include"Circumstance.h"
#include"Unit.h"
#include"ModernArmy.h"
struct Supply {
	double army1LapSupplies = 0;
	double army2LapSupplies = 0;
	int army1SupplyLapsAmount = 0;
	int army2SupplyLapsAmount = 0;
};
class BattleModeling
{
private:
	ModernArmy army1;
	ModernArmy army2;
	ModernArmy army1Reinforcements;
	ModernArmy army2Reinforcements;
	Supply lapSupplies;
	void battleLap();
	std::vector<ModernCircumstance> circumstances;
	ModernCircumstance getSummCircumstance();
public:
	BattleModeling(ModernArmy& army1, ModernArmy& army2);
	void addCircumstance(ModernCircumstance& circ);
	void setLapSupplies(Supply& supply);
	Supply getLapSupplies() const;
	void setReinforcements(ModernArmy& army1Reinforcements, ModernArmy& army2Reinforcements);
	void setSupplies(Supply& lapSupplies);
	void setSupplies(Supply lapSupplies);
	void operator()();
};

