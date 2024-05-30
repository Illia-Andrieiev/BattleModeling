#pragma once
#include<mutex>
#include<vector>
#include<map>
#include<iostream>
#include"Item.h"
#include"Cloneable.h"
#include"Army.h"
#include"libs/boost/ut.hpp"
class Unit;
class Army;
class AttackArmyTest;
class UnitTest;
/// Class for template method attack army for Unit
class AttackArmy {
	friend class AttackArmyTest;
private:
	double damage;

protected:
	virtual bool prepareForAttack(const double& supplies) { return true; };
	virtual double determineDamage(unitHelpers::unitTypes type, double power) { return damage; };
	virtual void manageSupplies(double& supplies, double power) {};
	bool fortificationTarget; ///< Always attack fortifications first
	AttackArmy(double damage, bool fortificationTarget);
	virtual int chooseTargetNomer(std::vector<Unit*>& units, int firstAlive);
	virtual double determinePower() { return damage; };
	
	virtual void attackFortification(Unit& fortification, double& damage);
	virtual int attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<Unit*>& units);
	virtual unitHelpers::unitTypes chooseTarget(Army& army) const;
	static unitHelpers::unitTypes chooseRandomTarget(Army& army);
public:
	virtual void attackArmy(Army& army, double& supplies);
};
class AttackArmyTest {
private:
	void attackFortificationTest();
	void attackUnitTypeTest();
public:
	void test();
};
class UnitBuilder;
/// Unit class for representing units on battle field
class Unit :public Cloneable<typename Unit*>, public Prototype<typename Unit*>, public AttackArmy
{
	friend class Army;
	friend class UnitBuilder;
	friend class FileManager;
	friend class AttackArmyTest;
	friend class UnitTest;
private:
	const int TYPE_ID = 0; ///< TYPE ID
protected:
	char name[256]; ///< Unit`s name
	bool alive; ///< Is unit can influence on battle
	double minPower; ///< Default unit damage
	double maxPower; ///< Default unit damage
	double maxArmor; ///< Default and maximum armor, that unit can have
	double currentArmor; ///< Current armor value
	bool isRenovateArmor; ///< Is renovate armor from supplies
	double viability; ///< Display unit`s chance to survive 
	std::mutex mt; ///< mutex
	std::vector<Item> items; ///< All unit`s items
	unitHelpers::Cycling cycling; ///< Cycling unit on battlefield
	std::map<unitHelpers::unitTypes, double> powerCoef; ///< Multiply on default damage to another unit`s types 
	unitHelpers::unitTypes type; ///< Unit`s type
	unitHelpers::unitTypes priorityTarget; ///< Preferable Units type to attack 
	std::string boolToStr(bool flag);
	virtual void renovateArmor(double& supplies);
	virtual bool prepareForAttack(const double& supplies) override;
	virtual void manageSupplies(double& supplies, double power) override;
	virtual double determineDamage(unitHelpers::unitTypes type, double power) override;
	virtual double determinePower() override;
	virtual unitHelpers::unitTypes chooseTarget(Army& army) const override;
	bool isMapsEqual(std::map<unitHelpers::unitTypes, double> map1, std::map<unitHelpers::unitTypes, double> map2);
public:
	virtual int getTypeID();
	Unit();
	virtual ~Unit() = default;
	Unit(const Unit& unit);
	void setPowerCoef(const std::pair<unitHelpers::unitTypes, double>& powerCoef);
	void setCycling(const unitHelpers::Cycling& cycling);
	Unit& operator =(const Unit& unit);
	virtual bool isEqual(Unit* unit);
	bool isAlive() const;
	bool getFortificationTarget() const;
	bool getIsRenovateArmor() const;
	double getMaxArmor() const;
	void applyItems();
	int attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<Unit*>& units) override;
	double getMaxBasePower() const;
	double getMinBasePower() const;
	double getViability() const;
	virtual void operator()(Army& army, double& supplies);
	virtual void takeDamage(double& damage);
	std::string getName() const;
	std::vector<Item> getItems() const;
	void multiplyPower(double koef);
	virtual std::string toString();
	bool getIsActive() const;
	std::map<unitHelpers::unitTypes, double> getPowerCoef() const;
	virtual void updateCycle();
	double getCurrentArmor() const;
	Unit* clone() const override;
	Unit* create() const override;
	void removeItem(const std::string& itemName);
	unitHelpers::unitTypes getType() const;
	unitHelpers::unitTypes getPriorityTargetType() const;
	unitHelpers::Cycling getCycling() const;
	void addItem(const Item& item);
};

/// Base Unit`s abstract builder
class BaseUnitBuilder {
public:
	virtual std::shared_ptr<Unit> getResult()=0;
	virtual void reset()=0;
	virtual BaseUnitBuilder* setName(const std::string& name) = 0;
	virtual BaseUnitBuilder* addItem(const Item& item) = 0;
	virtual BaseUnitBuilder* setPowerAndViability(double minPower, double maxPower, double viability) = 0;
	virtual BaseUnitBuilder* setFortificationTarget(bool fortificationTarget) = 0;
	virtual BaseUnitBuilder* setTypes(unitHelpers::unitTypes type, unitHelpers::unitTypes priorityTarget) = 0;
	virtual BaseUnitBuilder* setPowerCoef(const std::map<unitHelpers::unitTypes, double>& powerCoef) = 0;
	virtual BaseUnitBuilder* setCycling(const unitHelpers::Cycling& cycling) = 0;
	virtual BaseUnitBuilder* setArmor(double armor, bool isRenovate) = 0;
};
/// Concrete Unit builder
class UnitBuilder :public BaseUnitBuilder {
private:
	std::shared_ptr<Unit> unit;
public:
	UnitBuilder();
	virtual void reset() override;
	virtual std::shared_ptr<Unit> getResult() override;
	virtual UnitBuilder* setName(const std::string& name) override;
	virtual UnitBuilder* addItem(const Item& item) override;
	virtual UnitBuilder* setPowerAndViability(double minPower, double maxPower, double viability) override;
	virtual UnitBuilder* setFortificationTarget(bool fortificationTarget) override;
	virtual UnitBuilder* setTypes(unitHelpers::unitTypes type, unitHelpers::unitTypes priorityTarget) override;
	virtual UnitBuilder* setPowerCoef(const std::map<unitHelpers::unitTypes, double>& powerCoef) override;
	virtual UnitBuilder* setCycling(const unitHelpers::Cycling& cycling) override;
	virtual UnitBuilder* setArmor(double armor, bool isRenovate) override;
};
class UnitTest {
	UnitBuilder builder;
	void isEqualTest();
	void applyItemsTest();
	void takeDamageTest();
	void updateCycleTest();
	void cloneTest();
	void createTest();

public:
	UnitTest();
	void test();
};