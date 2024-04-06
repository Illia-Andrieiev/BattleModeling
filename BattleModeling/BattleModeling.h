#pragma once
#include<vector>
#include"Circumstance.h"
#include"Unit.h"
#include"ModernArmy.h"
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
	ModernArmy army1;
	ModernArmy army2;
	ModernArmy army1Reinforcements;
	ModernArmy army2Reinforcements;
	Supply lapSupplies;
	BattleModeling();
	void battleLap();
	std::vector<ModernCircumstance> circumstances;
	ModernCircumstance getSummCircumstance();
public:
	static BattleModeling* getBattleModeling();
	void addCircumstance(ModernCircumstance& circ);
	
	Supply getSupplies() const;

	void operator()();
};


class Builder {
public:
	virtual void reset()=0;
	virtual BattleModeling* getResult()=0;
	virtual Builder* setSupplies(Supply& lapSupplies)=0;
	virtual Builder* setReinforcements(ModernArmy& army1Reinforcements, ModernArmy& army2Reinforcements) = 0;
	virtual Builder* setArmy(ModernArmy& army1, ModernArmy& army2) = 0;
};
class BattleBuilder:public Builder {
	BattleModeling* battle;
public:
	BattleBuilder();
	void reset() override;
	BattleModeling* getResult() override;
	Builder* setSupplies(Supply& lapSupplies) override;
	Builder* setReinforcements(ModernArmy& army1Reinforcements, ModernArmy& army2Reinforcements)override;
	Builder* setArmy(ModernArmy& army1, ModernArmy& army2) override;
};