#pragma once
#include<vector>
#include"Unit.h"
#include"Circumstance.h"
#include<mutex>
#include<memory>
class Iterator;
/// Interface to crate iterators
class ArmyCollection {
public:
	virtual Iterator* createSequentiallyTypeIterator() = 0;
	virtual Iterator* createEachTypeIterator() = 0;
};
class Unit;
class Army;
class MementoArmy {
	friend class Army;
	std::vector<std::vector<Unit*>> units;
	Unit* fortification;
	double supplies;
	int round;
	std::shared_ptr<MementoArmy> prev;
public:
	MementoArmy(const Army& army, int round);
	~MementoArmy();
	void setPrevMemento(MementoArmy* memento);
	void setPrevMemento(std::shared_ptr<MementoArmy> memento);
};
/// Class to represent army on battle field
class Army : public ArmyCollection
{
	friend class Unit;
	friend class BattleModeling;
	friend class FileManager;
	friend class AttackArmy;
	friend class MementoArmy;
protected:
	char name[256];
	std::vector<std::vector<Unit*>> units;///< All army units. Each subVector represent each unit type  
	std::map<unitHelpers::unitTypes, int> unitTypesPositions;///< Positions of unit`s types in unit vector
	std::mutex mt;
	double supplies; ///< Current available supplies. Represent can units attack, or not
	Unit* fortification; ///< Take 50% of all foe`s units damage and damage them. By default viability and power = 0.  
	std::map<unitHelpers::unitTypes, double> power; ///< General army power
	double viability; ///< General army viability
	std::vector<int> positionOfFirstAlive; ///< Positions of first alive unit in appropriate vectors.
	void attackType(Army& army, std::vector<Unit*>& type, int posFirstAlive);
	void sortType(std::vector<Unit*>& units);
	void addUnitTest();
public:
	Army();
	Army(Unit& fortification);
	Army(const Army& army);
	~Army();
	void countPower();
	double getSupplies() const;
	void changeSupplies(double supply);
	int getAmountOfUniqueUnits();
	double getViability() const;
	double countViability();
	std::map<unitHelpers::unitTypes, double> getPower() const;
	void addUnit(Unit& unit, int amount);
	void attackArmy(Army& army);
	std::string toString();
	Army& operator =(const Army& army);
	void applyItems();
	void applyCircumstance(const Circumstance& circ);
	void sort();
	void setName(const std::string& name);
	bool isUnitsEqual(const Army& other) const;
	std::string getName();
	Iterator* createSequentiallyTypeIterator() override;
	Iterator* createEachTypeIterator() override;
	std::shared_ptr<MementoArmy> createMemento(int round);
	void reinstateMemento(MementoArmy* memento);
	void reinstateMemento(std::shared_ptr<MementoArmy> memento);
};
class ArmyTest :public Army {
	Army army;
	Army sortedArmy;
	void sortTest();
	void isUitsEqualTest();
	void getAmountOfUniqueUnitsTest();
public:
	ArmyTest();
	void test();
};
/// Iterator interface
class Iterator {
public:
	virtual Unit* getNext() = 0;
	virtual bool hasMore() = 0;
};

/// Return units in ascending order of raw number
class EachTypeIterator : public Iterator
{
private:
	const std::vector<std::vector<Unit*>>& units;
	int curI, curJ;
public:
	EachTypeIterator(const std::vector<std::vector<Unit*>>& units);
	bool hasMore() override;
	Unit* getNext() override;
};
/// Return units in ascending order of column number
class SequentiallyTypeIterator : public Iterator
{
private:
	std::vector<std::vector<Unit*>> units;
	int curI, curJ;
public:
	SequentiallyTypeIterator(const std::vector<std::vector<Unit*>>& units);
	bool hasMore() override;
	Unit* getNext() override;
};