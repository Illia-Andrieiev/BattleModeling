#include "MoralUnit.h"
#include <random>
MoralUnit::MoralUnit() {
	this->morality = 100;
	this->rateOfMoralityChanges = 1;
}
int MoralUnit::getTypeID() {
	return TYPE_ID;
}
double MoralUnit::getMorality() const {
	return morality;
}
MoralUnit& MoralUnit::operator = (const MoralUnit& unit) {
	if (this == &unit)
		return *this;
	this->cycling = unit.cycling;
	this->fortificationTarget = unit.fortificationTarget;
	for (int i = 0; i < 256; i++)
		this->name[i] = unit.name[i];
	this->minPower = unit.minPower;
	this->maxPower = unit.maxPower;
	this->morality = unit.morality;
	this->viability = unit.viability;
	this->powerCoef = unit.powerCoef;
	this->type = unit.type;
	this->items = unit.items;
	this->isRenovateArmor = unit.isRenovateArmor;
	this->maxArmor = unit.maxArmor;
	this->currentArmor = unit.currentArmor;
	this->priorityTarget = unit.priorityTarget;
	return *this;
}

void MoralUnit::setMorality(double morality) {
	if (morality < 0)
		morality = 0;
	if (morality > 100)
		morality = 100;
	this->morality = morality;
}
/// Decrease viability on damage points. If viability <= 0 set alive = false. 
/*!
*  Decrease damage on viability points. Set new morailty as old_morality * coef, where 
*  coef = new_viabiliy/old_viability. 0.5 <= coef < 1.
*/
void MoralUnit::takeDamage(double& damage) {
	this->viability -= damage;
	if (viability <= 0) {
		alive = false;
		damage = -viability;
		viability = 0;
	}
	else {
		double coef = (this->viability / (this->viability + damage));
		coef < 0.5 ? coef = 0.5 : coef = coef;
		this->morality = this->morality * coef;
		damage = 0;
	}
}
/// Add 1 to current cycle. Manage isActive atribute. 
/*!
*   Increase morality by 2 each unactive round, decrease by 0.5 each active,
*   and increase by 3.5 at round, when unit go unactive. 
*/
void MoralUnit::updateCycle() {
	if (cycling.isActive) {
		cycling.currentCycle++;
		if (cycling.currentCycle >= cycling.cyclesToReplenishment) {
			cycling.currentCycle = 0;
			cycling.isActive = false;
			setMorality(this->morality + 3.5);
			return;
		}
		setMorality(this->morality - 0.5*rateOfMoralityChanges);
	}
	else {
		cycling.currentCycle++;
		if (cycling.currentCycle >= cycling.cyclesToActivation) {
			cycling.currentCycle = 0;
			cycling.isActive = true;
			return;
		}
		setMorality(this->morality + 2);
	}
}
/// Determine how much damage unit will cause on battle field. Use normal_distribution.
/*!
*   if morality >= 50 && morality < 85 : axPower = minPower + (maxPower - minPower) * morality / 100;
*   if morality < 50 : minPower *= (morality + 50) / 100, maxPower = minPower + (maxPower - minPower) * morality / 100;
*/
double MoralUnit::determinePower(double minPower, double maxPower) {
	if (morality >= 50 && morality < 85) {
		maxPower = minPower + (maxPower - minPower) * morality / 100;
	}
	if(morality < 50) {
		double coef = (morality + 50) / 100;
		minPower *= coef;
		maxPower = minPower + (maxPower - minPower) * morality / 100;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> distr(minPower, maxPower);
	return distr(gen);
}
void MoralUnit::attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<Unit*>& units) {
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
			setMorality(this->morality + 5);
		}
	}
}
std::string MoralUnit::toString() {
	return Unit::toString() + " morality: " + std::to_string(morality);
}
MoralUnit* MoralUnit::clone() {
	MoralUnit* newUnit = new MoralUnit();
	newUnit->cycling = this->cycling;
	newUnit->fortificationTarget = this->fortificationTarget;
	for (int i = 0; i < 256; i++)
		newUnit->name[i] = this->name[i];
	newUnit->minPower = this->minPower;
	newUnit->maxPower = this->maxPower;
	newUnit->morality = this->morality;
	newUnit->rateOfMoralityChanges = this->rateOfMoralityChanges;
	newUnit->viability = this->viability;
	newUnit->powerCoef = this->powerCoef;
	newUnit->type = this->type;
	newUnit->items = this->items;
	newUnit->priorityTarget = this->priorityTarget;
	newUnit->isRenovateArmor = this->isRenovateArmor;
	newUnit->maxArmor = this->maxArmor;
	newUnit->currentArmor = this->currentArmor;
	return newUnit;
}
MoralUnit* MoralUnit::create() {
	MoralUnit* res = new MoralUnit();
	res->type = this->type;
	res->priorityTarget = this->priorityTarget;
	return res;
}
bool MoralUnit::isEqual(Unit* unit) {
	MoralUnit* unit1 = dynamic_cast<MoralUnit*>(unit);
	if (unit1 == nullptr || items.size() != unit1->items.size() || unit1->getTypeID() != TYPE_ID) {
		return false;
	}
	for (int i = 0; i < items.size(); i++) {
		if (!(items[i].isEqual(unit1->items[i])))
			return false;
	}
	return this->alive == unit1->alive && this->currentArmor == unit1->currentArmor && this->cycling.isEqual(unit1->cycling) &&
		this->morality == unit1->morality && this->rateOfMoralityChanges == unit1->rateOfMoralityChanges &&
		this->fortificationTarget == unit1->fortificationTarget && this->isRenovateArmor == unit1->isRenovateArmor &&
		this->maxArmor == unit1->maxArmor && this->maxPower == unit1->maxPower && this->minPower == unit1->minPower &&
		this->type == unit1->type && this->viability == unit1->viability && this->priorityTarget == unit1->priorityTarget
		&& isMapsEqual(this->powerCoef, unit1->powerCoef);
}
/*
	Builder
*/
MoralUnitBuilder::MoralUnitBuilder() {
	reset();
}
void MoralUnitBuilder::reset() {
	unit = MoralUnit();
}
MoralUnit& MoralUnitBuilder::getResult() {
	return unit;
}
MoralUnitBuilder* MoralUnitBuilder::setName(const std::string& name) {
	int i;
	for (i = 0; i < name.size() && i < 256; i++) {
		unit.name[i] = name[i];
	}
	for (; i < 256; i++) {
		unit.name[i] = '\0';
	}
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::addItem(const Item& item) {
	unit.items.push_back(item);
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setPowerAndViability(double minPower, double maxPower, double viability) {
	if (minPower < 0 || maxPower <= 0 || viability <= 0)
		return this;
	unit.minPower = minPower;
	unit.maxPower = maxPower;
	unit.viability = viability;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setFortificationTarget(bool fortificationTarget) {
	unit.fortificationTarget = fortificationTarget;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setTypes(unitHelpers::unitTypes type, unitHelpers::unitTypes priorityTarget) {
	unit.type = type;
	unit.priorityTarget = priorityTarget;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setPowerCoef(const std::map<unitHelpers::unitTypes, double>& powerCoef) {
	unit.powerCoef = powerCoef;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setCycling(const unitHelpers::Cycling& cycling) {
	unit.cycling = cycling;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setMorality(double morality, double rateOfMoralityChanges = 1) {
	unit.setMorality(morality);
	if (rateOfMoralityChanges <= 0)
		rateOfMoralityChanges = 1;
	unit.rateOfMoralityChanges = rateOfMoralityChanges;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setArmor(double armor, bool isRenovate) {
	if (armor < 0)
		armor = 0;
	unit.currentArmor = armor;
	unit.maxArmor = armor;
	unit.isRenovateArmor = isRenovate;
	return this;
}