#include "ModernUnit.h"
#include<random>
ModernUnit::ModernUnit(std::string name, double power, double viability, bool fortificationTarget, unitHelpers::Cycling cycling,
	unitHelpers::ModernPowerCoef powerCoef):Unit(name,power,viability) {
	this->cycling = cycling;
	this->powerCoef = powerCoef;
	this->fortificationTarget = fortificationTarget;
}
ModernUnit::ModernUnit(std::string name, double power, double viability, bool fortificationTarget, std::vector<Item>& items,
	unitHelpers::Cycling cycling, unitHelpers::ModernPowerCoef powerCoef) :Unit(name, power, viability, items) {
	this->cycling = cycling;
	this->powerCoef = powerCoef;
	this->fortificationTarget = fortificationTarget;
}
ModernUnit ModernUnit::clone(){
	return ModernUnit(this->name, this->power, this->viability, this->fortificationTarget, this->items, this->cycling, this->powerCoef);
}