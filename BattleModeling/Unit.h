#pragma once
#include<vector>
#include"Item.h"
#include"Clonable.h"
#include<iostream>
class Unit
{
protected:
	char name[256]; /// Unit`s name
	bool alive; /// Is unit can influence on battle
	double power; /// Default unit damage
	double viability; /// Display unit`s chance to survive 
	std::vector<Item> items; /// All unit`s items
	double morality;
	std::string boolToStr(bool flag);
public:
	Unit(std::string name, double power, double viability);
	Unit(std::string name, double power, double viability,const std::vector<Item>& items);
	bool isAlive() const;
	virtual void applyItems();
	double getBasePower() const;
	double getViability() const;
	void takeDamage(double& damage);
	std::string getName() const;
	std::vector<Item> getItems() const;
	void multiplyPower(double koef);
	void setMorality(double newMorality);
	double getMorality() const;
	virtual std::string toString();
};

