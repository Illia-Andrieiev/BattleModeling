#include "ModernUnit.h"
ModernUnit::ModernUnit(char name[256], double power, double viability, bool fortificationTarget, Cycling cycling,
	ModernPowerCoef powerCoef):Unit(name,power,viability) {
	this->cycling = cycling;
	this->powerCoef = powerCoef;
	this->fortificationTarget = fortificationTarget;
}
ModernUnit::ModernUnit(char name[256], double power, double viability, bool fortificationTarget, std::vector<Item>& items,
	Cycling cycling, ModernPowerCoef powerCoef) :Unit(name, power, viability, items) {
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
ModernPowerCoef ModernUnit::getPowerCoef() const{
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