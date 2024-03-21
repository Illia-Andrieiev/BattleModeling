#pragma once
#include<vector>
#include"ModernUnit.h"
#include<mutex>
class ModernUnit;
class ModernArmy
{
	friend ModernUnit;
	std::vector<ModernUnit> aviation;/// All aviation units
	std::vector<ModernUnit> vehickles;/// All ArmoredVehickle units
	std::vector<ModernUnit> infantry;/// All infantry units
	std::vector<ModernUnit> artilery; /// All artilery units
	std::mutex mt;
	Unit fortification; /// Take 50% of all foe`s units damage and damage them. By default viability and power = 0.  
	ModernPowerCoef power; /// General army power
	double viability; /// General army viability
	int positionOfFirstAlive[4]; /// Positions of first alive unit in appropriate vectors. 0-aviation, 1-vehickles, 2-infantry, 3-artilery
	void attackType(ModernArmy& army, std::vector<ModernUnit>& type, int posFirstAlive);
public:
	ModernArmy();
	void countPower();
	double getViability();
	double countViability();
	void addUnit(ModernUnit& unit, modernUnitTypes type);
	void attackArmy(ModernArmy& army);
	std::string toString();
	ModernArmy& operator =(const ModernArmy& army);
};

