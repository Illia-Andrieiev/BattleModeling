#pragma once
#include<vector>
#include"Unit.h"
#include"Circumstance.h"
#include<mutex>
class ModernUnit;
class Army: public Cloneable<typename Army>
{
	friend class Unit;
	std::vector<std::vector<Unit*>> units;/// All army units. Each subVector represent each unit type  
	std::map<unitHelpers::unitTypes, int> unitTypesPositions;/// Positions of unit`s types in unit vector
	std::mutex mt;
	double supplies; /// Current available supplies. Represent can units attack, or not
	Unit fortification; /// Take 50% of all foe`s units damage and damage them. By default viability and power = 0.  
	unitHelpers::ModernPowerCoef power; /// General army power
	double viability; /// General army viability
	std::vector<int> positionOfFirstAlive; /// Positions of first alive unit in appropriate vectors.
	void attackType(Army& army, std::vector<ModernUnit>& type, int posFirstAlive);
public:
	Army();
	Army(const Unit& fortification);
	Army(const Army& army);
	~Army();
	Army clone() override;
	void countPower();
	double getSupplies() const;
	void changeSupplies(double supply);
	double getViability() const;
	double countViability();
	void addUnit(const ModernUnit& unit, unitHelpers::unitTypes type);
	void attackArmy(Army& army);
	std::string toString();
	Army& operator =(const Army& army);
	void applyItems();
	void applyCircumstance(const ModernCircumstance& circ);
};

