#include "Unit.h"
#include<random>
/// Return is unit alive
bool Unit::isAlive() const{
	return alive;
}
/// Constructor
Unit::Unit() {
	this->power = 0;
	std::string name = "default";
	for (int i = 0; i<name.size() && i < 256; i++)
		this->name[i] = name[i];
	this->viability = 0;
	this->alive = true;
	this->morality = 100;
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
/// Add to unit`s viability and power appropriated parameters from item
void Unit::applyItems() {
	for (int i = 0; i < items.size();i++) {
		if (!items[i].isApply()) {
			items[i].apply();
			power += items[i].getBasePowerChanges();
			viability += items[i].getViabilityChanges();
		}
	}
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
unitHelpers::ModernPowerCoef Unit::getTypesPower() const {
	return unitHelpers::ModernPowerCoef(power * powerCoef.aviationDamagekoef, power * powerCoef.infantryDamagekoef,
		power * powerCoef.vehickleDamagekoef, power * powerCoef.artileryDamagekoef);
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
			powerCoef = powerCoef * items[i].getPowerChanges();
		}
	}
}
/// Choose type of unit to attack.
/*!
* Use uniform_real_distribution. Weight of types to attack defines as power*unit`sTypeCoef
*/
unitHelpers::unitTypes Unit::chooseTarget(ModernArmy& army) const {
	double aviationParam = power * powerCoef.aviationDamagekoef;
	double artileryParam = aviationParam + power * powerCoef.artileryDamagekoef;
	double infantryParam = artileryParam + power * powerCoef.infantryDamagekoef;
	double summPower = infantryParam + power * powerCoef.vehickleDamagekoef;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(0, summPower);
	for (int i = 0; i < 100; i++) {
		double param = distr(gen);
		if (param <= aviationParam && army.positionOfFirstAlive[0] != -1)
			return unitHelpers::unitTypes::aviation;
		if (param <= artileryParam && army.positionOfFirstAlive[3] != -1)
			return unitHelpers::unitTypes::artilery;
		if (param <= infantryParam && army.positionOfFirstAlive[2] != -1)
			return unitHelpers::unitTypes::infantry;
		if (param <= summPower && army.positionOfFirstAlive[1] != -1)
			return unitHelpers::unitTypes::armoredVehickle;
	}
	return unitHelpers::unitTypes::infantry;
}
void Unit::attackFortification(Unit& fortification, double& damage) {
	if (fortification.isAlive()) {
		double dam = damage / 2;
		fortification.takeDamage(dam);
		damage = damage / 2 + dam;
	}
}
int Unit::chooseTargetNomer(std::vector<ModernUnit>& units, int firstAlive) {
	if (firstAlive == -1)
		return -1;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(firstAlive, (int)units.size() - 1);
	return distr(gen);
}
void Unit::attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<ModernUnit>& units) {
	if (posFirstAlive == -1 || units.size() == 0)
		return;
	attackFortification(fortification, damage);
	while (damage > 0 && posFirstAlive != -1) {
		int pos = chooseTargetNomer(units, posFirstAlive);
		units[pos].takeDamage(damage);
		if (!units[pos].isAlive()) {
			std::swap(units[pos], units[posFirstAlive]);
			posFirstAlive++;
			if (posFirstAlive == units.size()) {
				posFirstAlive = -1;
			}
		}
	}
}
void Unit::attackArmy(ModernArmy& army, double& supplies) {
	if (supplies <= 0)
		return;
	supplies -= power * 0.1;
	supplies = supplies < 0 ? 0 : supplies;
	unitHelpers::unitTypes type = chooseTarget(army);
	if (type == unitHelpers::unitTypes::aviation) {
		double damage = power * powerCoef.aviationDamagekoef;
		attackUnitType(army.fortification, damage, army.positionOfFirstAlive[0], army.aviation);
	}
	if (type == unitHelpers::unitTypes::artilery) {
		double damage = power * powerCoef.artileryDamagekoef;
		attackUnitType(army.fortification, damage, army.positionOfFirstAlive[3], army.artilery);
	}
	if (type == unitHelpers::unitTypes::infantry) {
		double damage = power * powerCoef.infantryDamagekoef;
		attackUnitType(army.fortification, damage, army.positionOfFirstAlive[2], army.infantry);
	}
	if (type == unitHelpers::unitTypes::armoredVehickle) {
		double damage = power * powerCoef.vehickleDamagekoef;
		attackUnitType(army.fortification, damage, army.positionOfFirstAlive[1], army.vehickles);
	}
}

/*

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
	for (int i = 0; i < name.size() && i < 256; i++)
		unit.name[i] = name[i];
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