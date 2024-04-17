#pragma once
#include<vector>
#include<map>
#include<iostream>
#include"Item.h"
#include"Clonable.h"
#include"Army.h"

class UnitBuilder;
class Unit:public Cloneable<typename Unit*>
{
	friend class Army;
	friend class UnitBuilder;
protected:
	char name[256]; /// Unit`s name
	bool alive; /// Is unit can influence on battle
	double power; /// Default unit damage
	double viability; /// Display unit`s chance to survive 
	std::vector<Item> items; /// All unit`s items
	double morality;
	bool fortificationTarget; /// Always attack fortifications first
	unitHelpers::Cycling cycling; /// Cycling unit on battlefield
	std::map<unitHelpers::unitTypes, double> powerCoef; /// Multiply on default damage to another unit`s types 
	unitHelpers::unitTypes type; /// Unit`s type
	unitHelpers::unitTypes priorityTarget; /// Preferable Units type to attack 
	unitHelpers::unitTypes chooseTarget(Army& army) const;
	int chooseTargetNomer(std::vector<Unit*>& units, int firstAlive);
	void attackFortification(Unit& fortification, double& damage);
	void attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<Unit*>& units);
	std::string boolToStr(bool flag);
public:
	Unit();
	bool isAlive() const;
	void applyItems();
	double getBasePower() const;
	double getViability() const;
	void takeDamage(double& damage);
	std::string getName() const;
	std::vector<Item> getItems() const;
	void multiplyPower(double koef);
	void setMorality(double newMorality);
	double getMorality() const;
	virtual std::string toString();
	bool getIsActive() const;
	std::map<unitHelpers::unitTypes, double> getPowerCoef() const;
	void updateCycle();
	virtual void attackArmy(Army& army, double& supplies);
	Unit* clone();
};
class UnitBuilder {
private:
	Unit unit;
public:
	UnitBuilder();
	void reset();
	Unit& getResult();
	UnitBuilder* setName(const std::string& name);
	UnitBuilder* addItem(const Item& item);
	UnitBuilder* setPowerAndViability(double power, double viability);
	UnitBuilder* setFortificationTarget(bool fortificationTarget);
	UnitBuilder* setTypes(unitHelpers::unitTypes type, unitHelpers::unitTypes priorityTarget);
	UnitBuilder* setPowerCoef(const std::map<unitHelpers::unitTypes, double>& powerCoef);
	UnitBuilder* setCycling(const unitHelpers::Cycling& cycling);
};