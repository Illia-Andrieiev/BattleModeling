#pragma once
#include<vector>
#include"ModernUnit.h"
#include"Circumstance.h"
#include<mutex>
class ModernUnit;
class ModernArmy: public Clonable<typename ModernArmy>
{
	friend ModernUnit;
	std::vector<ModernUnit> aviation;/// All aviation units
	std::vector<ModernUnit> vehickles;/// All ArmoredVehickle units
	std::vector<ModernUnit> infantry;/// All infantry units
	std::vector<ModernUnit> artilery; /// All artilery units
	std::mutex mt;
	double supplies; /// Current available supplies. Represent can units attack, or not
	Unit fortification; /// Take 50% of all foe`s units damage and damage them. By default viability and power = 0.  
	modern::ModernPowerCoef power; /// General army power
	double viability; /// General army viability
	int positionOfFirstAlive[4]; /// Positions of first alive unit in appropriate vectors. 0-aviation, 1-vehickles, 2-infantry, 3-artilery
	void attackType(ModernArmy& army, std::vector<ModernUnit>& type, int posFirstAlive);
public:
	ModernArmy();
	ModernArmy(Unit& fortification);
	ModernArmy(const ModernArmy& army);
	ModernArmy clone() override;
	void countPower();
	double getSupplies() const;
	void changeSupplies(double supply);
	double getViability() const;
	double countViability();
	void addUnit(const ModernUnit& unit, modern::modernUnitTypes type);
	void attackArmy(ModernArmy& army);
	std::string toString();
	ModernArmy& operator =(const ModernArmy& army);
	void applyItems();
	void applyCircumstance(const ModernCircumstance& circ);
};

