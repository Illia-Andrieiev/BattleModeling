#pragma once
#include<vector>
#include"Item.h"
class Unit
{
private:
	char name[256]; /// Unit`s name
	bool alive; /// Is unit can influence on battle
	Power power; /// Display how much unit influence on foe`s army
	double viability; /// Display unit`s chance to survive 
	std::vector<Item> items; /// All unit`s items
public:
	Unit(char name[256], Power& power, double viability);
	Unit(char name[256], Power& power, double viability, std::vector<Item>& items);
	bool isAlive() const;
	Power getPower() const;
	void getDamage(double damage);
};

