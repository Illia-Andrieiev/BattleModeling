#pragma once
#include<vector>
#include"Aviation.h"
#include"ArmoredVehickle.h"
#include"Infantry.h"
#include"Artilery.h"
class Army
{

public:
	std::vector<Unit> aviation;/// All aviation units
	std::vector<Unit> vehickles;/// All ArmoredVehickle units
	std::vector<Unit> infantry;/// All infantry units
	std::vector<Unit> artilery; /// All artilery units
	Power power; /// General army power
	int positionOfLastAlive[4]; /// Positions of last alive unit in appropriate vectors
	double countPower();
	Army();
	Army(std::vector<Unit> units);
	void addUnit(Unit unit);
};

