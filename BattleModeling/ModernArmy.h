#pragma once
#include<vector>
#include"ModernUnit.h"
#include"Circumstance.h"
#include<mutex>
class ModernUnit;
class ModernArmy: public Cloneable<typename ModernArmy>
{
	friend ModernUnit;
	std::vector<std::vector<Unit*>> units;/// All army units. Each subVector represent each unit type  
	std::mutex mt;
	double supplies; /// Current available supplies. Represent can units attack, or not
	Unit fortification; /// Take 50% of all foe`s units damage and damage them. By default viability and power = 0.  
	unitHelpers::ModernPowerCoef power; /// General army power
	double viability; /// General army viability
	std::vector<int> positionOfFirstAlive; /// Positions of first alive unit in appropriate vectors.
	void attackType(ModernArmy& army, std::vector<ModernUnit>& type, int posFirstAlive);
public:
	ModernArmy();
	ModernArmy(Unit& fortification);
	ModernArmy(const ModernArmy& army);
	~ModernArmy();
	ModernArmy clone() override;
	void countPower();
	double getSupplies() const;
	void changeSupplies(double supply);
	double getViability() const;
	double countViability();
	void addUnit(const ModernUnit& unit, unitHelpers::unitTypes type);
	void attackArmy(ModernArmy& army);
	std::string toString();
	ModernArmy& operator =(const ModernArmy& army);
	void applyItems();
	void applyCircumstance(const ModernCircumstance& circ);
};

