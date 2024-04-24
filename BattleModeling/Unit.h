#pragma once
#include<vector>
#include<map>
#include<iostream>
#include"Item.h"
#include"Clonable.h"
#include"Army.h"

class UnitBuilder;
class Unit:public Cloneable<typename Unit*>, public Prototype<typename Unit*>
{
	friend class Army;
	friend class UnitBuilder;
	friend class FileManager;
private:
	const int TYPE_ID = 0;
protected:
	char name[256]; /// Unit`s name
	bool alive; /// Is unit can influence on battle
	double minPower; /// Default unit damage
	double maxPower; /// Default unit damage
	double maxArmor; /// Default and maximum armor, that unit can have
	double currentArmor; /// Current armor value
	bool isRenovateArmor; /// Is renovate armor from supplies
	double viability; /// Display unit`s chance to survive 
	std::vector<Item> items; /// All unit`s items
	bool fortificationTarget; /// Always attack fortifications first
	unitHelpers::Cycling cycling; /// Cycling unit on battlefield
	std::map<unitHelpers::unitTypes, double> powerCoef; /// Multiply on default damage to another unit`s types 
	unitHelpers::unitTypes type; /// Unit`s type
	unitHelpers::unitTypes priorityTarget; /// Preferable Units type to attack 
	unitHelpers::unitTypes chooseTarget(Army& army) const;
	int chooseTargetNomer(std::vector<Unit*>& units, int firstAlive);
	void attackFortification(Unit& fortification, double& damage);
	virtual void attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<Unit*>& units);
	std::string boolToStr(bool flag);
	virtual void renovateArmor(double& supplies);
	virtual double determinePower(double minPower, double maxPower);
	bool isMapsEqual(std::map<unitHelpers::unitTypes, double> map1, std::map<unitHelpers::unitTypes, double> map2);
public:
	virtual int getTypeID();
	Unit();
	Unit& operator = (const Unit& unit);
	virtual bool isEqual(Unit* unit);
	bool isAlive() const;
	void applyItems();
	double getMaxBasePower() const;
	double getMinBasePower() const;
	double getViability() const;
	virtual void takeDamage(double& damage);
	std::string getName() const;
	std::vector<Item> getItems() const;
	void multiplyPower(double koef);
	virtual std::string toString();
	bool getIsActive() const;
	std::map<unitHelpers::unitTypes, double> getPowerCoef() const;
	virtual void updateCycle();
	virtual void attackArmy(Army& army, double& supplies);
	Unit* clone() override;
	Unit* create() override;
	unitHelpers::unitTypes getType() const;

};
class BaseUnitBuilder {
public:
	virtual BaseUnitBuilder* setName(const std::string& name)=0;
	virtual BaseUnitBuilder* addItem(const Item& item) =0;
	virtual BaseUnitBuilder* setPowerAndViability(double minPower, double maxPower, double viability)=0;
	virtual BaseUnitBuilder* setFortificationTarget(bool fortificationTarget)=0;
	virtual BaseUnitBuilder* setTypes(unitHelpers::unitTypes type, unitHelpers::unitTypes priorityTarget)=0;
	virtual BaseUnitBuilder* setPowerCoef(const std::map<unitHelpers::unitTypes, double>& powerCoef)=0;
	virtual BaseUnitBuilder* setCycling(const unitHelpers::Cycling& cycling)=0;
	virtual BaseUnitBuilder* setArmor(double armor,bool isRenovate) = 0;
};

class UnitBuilder: BaseUnitBuilder{
private:
	Unit unit;
public:
	UnitBuilder();
	virtual void reset();
	virtual Unit& getResult();
	virtual UnitBuilder* setName(const std::string& name) override;
	virtual UnitBuilder* addItem(const Item& item) override;
	virtual UnitBuilder* setPowerAndViability(double minPower, double maxPower, double viability) override;
	virtual UnitBuilder* setFortificationTarget(bool fortificationTarget) override;
	virtual UnitBuilder* setTypes(unitHelpers::unitTypes type, unitHelpers::unitTypes priorityTarget) override;
	virtual UnitBuilder* setPowerCoef(const std::map<unitHelpers::unitTypes, double>& powerCoef) override;
	virtual UnitBuilder* setCycling(const unitHelpers::Cycling& cycling) override;
	virtual UnitBuilder* setArmor(double armor, bool isRenovate) override;
};