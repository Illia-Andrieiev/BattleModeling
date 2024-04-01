#include "ModernUnit.h"
#include<random>
ModernUnit::ModernUnit(std::string name, double power, double viability, bool fortificationTarget, modern::Cycling cycling,
	modern::ModernPowerCoef powerCoef):Unit(name,power,viability) {
	this->cycling = cycling;
	this->powerCoef = powerCoef;
	this->fortificationTarget = fortificationTarget;
}
ModernUnit::ModernUnit(std::string name, double power, double viability, bool fortificationTarget, std::vector<Item>& items,
	modern::Cycling cycling, modern::ModernPowerCoef powerCoef) :Unit(name, power, viability, items) {
	this->cycling = cycling;
	this->powerCoef = powerCoef;
	this->fortificationTarget = fortificationTarget;
}
ModernUnit ModernUnit::clone(){
	return ModernUnit(this->name, this->power, this->viability, this->fortificationTarget, this->items, this->cycling, this->powerCoef);
}
bool ModernUnit::getIsActive() const{
	return this->cycling.isActive;
}
modern::ModernPowerCoef ModernUnit::getPowerCoef() const{
	return this->powerCoef;
}
/// Add 1 to current cycle. Manage isActive atribute
void ModernUnit::updateCycle() {
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
modern::ModernPowerCoef ModernUnit::getTypesPower() const {
	return modern::ModernPowerCoef(power * powerCoef.aviationDamagekoef, power * powerCoef.infantryDamagekoef,
		power * powerCoef.vehickleDamagekoef, power * powerCoef.artileryDamagekoef);
}
/// At first add all don`t applied items base parameters changes tp unit. Then multiply item`s powerCoef on unit`s.
void ModernUnit::applyItems() {
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
modern::modernUnitTypes ModernUnit::chooseTarget(ModernArmy& army) const{
	double aviationParam = power * powerCoef.aviationDamagekoef;
	double artileryParam = aviationParam + power * powerCoef.artileryDamagekoef;
	double infantryParam = artileryParam + power * powerCoef.infantryDamagekoef;
	double summPower =  infantryParam + power * powerCoef.vehickleDamagekoef;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(0, summPower);
	for (int i = 0; i < 100;i++) {
		double param = distr(gen);
		if (param <= aviationParam && army.positionOfFirstAlive[0] != -1)
			return modern::modernUnitTypes::aviation;
		if (param <= artileryParam && army.positionOfFirstAlive[3] != -1)
			return modern::modernUnitTypes::artilery;
		if (param <= infantryParam && army.positionOfFirstAlive[2] != -1)
			return modern::modernUnitTypes::infantry;
		if(param <= summPower && army.positionOfFirstAlive[1] != -1)
			return modern::modernUnitTypes::armoredVehickle;
	}
	return modern::modernUnitTypes::infantry;
}
void ModernUnit::attackFortification(Unit& fortification, double& damage) {
	if (fortification.isAlive()) {
		double dam = damage / 2;
		fortification.takeDamage(dam);
		damage = damage / 2 + dam;
	}
}
int ModernUnit::chooseTargetNomer(std::vector<ModernUnit>& units, int firstAlive) {
	if (firstAlive == -1)
		return -1;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(firstAlive, (int)units.size()-1);
	return distr(gen);
}
void ModernUnit::attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<ModernUnit>& units) {
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
void ModernUnit::attackArmy(ModernArmy& army, double& supplies) {
	if (supplies <= 0)
		return;
	supplies -= power * 0.1;
	supplies = supplies < 0 ? 0 : supplies;
	modern::modernUnitTypes type = chooseTarget(army);
	if (type == modern::modernUnitTypes::aviation) {
		double damage = power * powerCoef.aviationDamagekoef;
		attackUnitType(army.fortification, damage, army.positionOfFirstAlive[0], army.aviation);
	}
	if (type == modern::modernUnitTypes::artilery) {
		double damage = power * powerCoef.artileryDamagekoef;
		attackUnitType(army.fortification, damage, army.positionOfFirstAlive[3], army.artilery);
	}
	if (type == modern::modernUnitTypes::infantry) {
		double damage = power * powerCoef.infantryDamagekoef;
		attackUnitType(army.fortification, damage, army.positionOfFirstAlive[2], army.infantry);
	}
	if (type == modern::modernUnitTypes::armoredVehickle) {
		double damage = power * powerCoef.vehickleDamagekoef;
		attackUnitType(army.fortification, damage, army.positionOfFirstAlive[1], army.vehickles);
	}
}