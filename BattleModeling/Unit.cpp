#include "Unit.h"
#include<random>
/// Return is unit alive
bool Unit::isAlive() const{
	return alive;
}
/// Constructor
Unit::Unit() {
	type = static_cast<unitHelpers::unitTypes>(0);
	priorityTarget = static_cast<unitHelpers::unitTypes>(0);
	this->power = 0;
	std::string name = "default";
	for (int i = 0; i<name.size() && i < 256; i++)
		this->name[i] = name[i];
	this->viability = 0;
	this->alive = true;
	this->morality = 100;
	fortificationTarget = false;
}

/// Decrease viability on damage. If viability <= 0 set alive = false. Decrease damage on viability points
void Unit::takeDamage(double& damage) {
	this->viability -= damage;
	if (viability <= 0) {
		alive = false;
		damage = -viability;
		viability = 0;
	}
	else
		damage = 0;
}
double Unit::getBasePower() const {
	return power;
}
std::string Unit::getName() const{
	return std::string(name);
}
double Unit::getViability() const {
	return viability;
}
std::vector<Item> Unit::getItems() const {
	return items;
}

void Unit::setMorality(double newMorality) {
	if (newMorality > 100) {
		morality = 100;
		return;
	}
	if (newMorality < 0) {
		morality = 0;
	}
	else
		morality = newMorality;
}
double Unit::getMorality() const {
	return morality;
}
std::string Unit::boolToStr(bool flag) {
	return flag ? "true": "false";
}
std::string Unit::toString() {
	return std::string("Name: " + std::string(name) + " viability: " + std::to_string(viability) + " alive: " + boolToStr(alive));
}
void Unit::multiplyPower(double koef) {
	if (koef < 0)
		return;
	this->power *= koef;
}
bool Unit::getIsActive() const {
	return this->cycling.isActive;
}
std::map<unitHelpers::unitTypes, double> Unit::getPowerCoef() const {
	return this->powerCoef;
}
/// Add 1 to current cycle. Manage isActive atribute
void Unit::updateCycle() {
	if (cycling.isActive) {
		cycling.currentCycle++;
		if (cycling.currentCycle >= cycling.cyclesToReplenishment) {
			cycling.currentCycle = 0;
			cycling.isActive = false;
		}
	}
	else {
		cycling.currentCycle++;
		if (cycling.currentCycle >= cycling.cyclesToActivation) {
			cycling.currentCycle = 0;
			cycling.isActive = true;
		}
	}
}

/// At first add all don`t applied items base parameters changes tp unit. Then multiply item`s powerCoef on unit`s.
void Unit::applyItems() {
	for (int i = 0; i < items.size(); i++) {
		if (!items[i].isApply()) {
			power += items[i].getBasePowerChanges();
			viability += items[i].getViabilityChanges();
		}
	}
	for (int i = 0; i < items.size(); i++) {
		if (!items[i].isApply()) {
			items[i].apply();
			for (auto& param : items[i].getPowerChanges()) {
				powerCoef[param.first] *= param.second;
			}
		}
	}
}
/// Choose type of unit to attack.
/*!
* Use uniform_real_distribution. Weight of types to attack defines as power*unit`sTypeCoef
*/
unitHelpers::unitTypes Unit::chooseTarget(Army& army) const {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, (int)army.units.size()-1);
	for (int i = 0; i < 100; i++) {
		int param = distr(gen);
		if (army.positionOfFirstAlive[army.unitTypesPositions[static_cast<unitHelpers::unitTypes>(param)]] != -1)
			return static_cast<unitHelpers::unitTypes>(param);
	}
	return static_cast<unitHelpers::unitTypes>(0);
}
void Unit::attackFortification(Unit& fortification, double& damage) {
	if (fortification.isAlive()) {
		double dam = damage / 2;
		fortification.takeDamage(dam);
		damage = damage / 2 + dam;
	}
}
int Unit::chooseTargetNomer(std::vector<Unit*>& units, int firstAlive) {
	if (firstAlive == -1)
		return -1;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(firstAlive, (int)units.size() - 1);
	for (int i = 0; i < 120; i++) {
		int pos = distr(gen);
		if (units[pos]->cycling.isActive)
			return pos;
	}
	return -1;
}
void Unit::attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<Unit*>& units) {
	attackFortification(fortification, damage);
	if (posFirstAlive == -1 || units.size() == 0)
		return;
	while (damage > 0 && posFirstAlive != -1) {
		int pos = chooseTargetNomer(units, posFirstAlive);
		if (pos == -1)
			return;
		units[pos]->takeDamage(damage);
		if (!units[pos]->isAlive()) {
			std::swap(units[pos], units[posFirstAlive]);
			posFirstAlive++;
			if (posFirstAlive == units.size()) {
				posFirstAlive = -1;
			}
		}
	}
}
void Unit::attackArmy(Army& army, double& supplies) {
	if (!cycling.isActive) {
		updateCycle();
		return;
	}
	updateCycle();
	if (supplies <= 0)
		return;
	supplies -= power * 0.1;
	supplies = supplies < 0 ? 0 : supplies;
	int posAlivePriorityTarget = army.positionOfFirstAlive[army.unitTypesPositions[priorityTarget]];
	unitHelpers::unitTypes type = priorityTarget;
	if(posAlivePriorityTarget == -1)
		type = chooseTarget(army);
	double damage = power * powerCoef[type];
	attackUnitType(*(army.fortification), damage, army.positionOfFirstAlive[army.unitTypesPositions[type]], army.units[army.unitTypesPositions[type]]);
}
Unit* Unit::clone() {
	Unit* newUnit = new Unit();
	newUnit->cycling = this->cycling;
	newUnit->fortificationTarget = this->fortificationTarget;
	for (int i = 0; i < 256; i++)
		newUnit->name[i] = this->name[i];
	newUnit->power = this->power;
	newUnit->viability = this->viability;
	newUnit->powerCoef = this->powerCoef;
	newUnit->type = this->type;
	newUnit->priorityTarget = this->priorityTarget;
	return newUnit;
}
/*
	Builder
*/
UnitBuilder::UnitBuilder() {
	reset();
}
void UnitBuilder::reset() {
	unit = Unit();
}
Unit& UnitBuilder::getResult() {
	return unit;
}
UnitBuilder* UnitBuilder::setName(const std::string& name) {
	int i;
	for (i = 0; i < name.size() && i < 256; i++) {
		unit.name[i] = name[i];
	}
	for (; i < 256; i++) {
		unit.name[i] = '\0';
	}
	return this;
}
UnitBuilder* UnitBuilder::addItem(const Item& item) {
	unit.items.push_back(item);
	return this;
}
UnitBuilder* UnitBuilder::setPowerAndViability(double power, double viability) {
	if (power <= 0)
		return this;
	if (viability <= 0)
		return this;
	unit.power = power;
	unit.viability = viability;
	return this;
}
UnitBuilder* UnitBuilder::setFortificationTarget(bool fortificationTarget) {
	unit.fortificationTarget = fortificationTarget;
	return this;
}
UnitBuilder* UnitBuilder::setTypes(unitHelpers::unitTypes type, unitHelpers::unitTypes priorityTarget) {
	unit.type = type;
	unit.priorityTarget = priorityTarget;
	return this;
}
UnitBuilder* UnitBuilder::setPowerCoef(const std::map<unitHelpers::unitTypes, double>& powerCoef) {
	unit.powerCoef = powerCoef;
	return this;
}
UnitBuilder* UnitBuilder::setCycling(const unitHelpers::Cycling& cycling) {
	unit.cycling = cycling;
	return this;
}