#include "Circumstance.h"
Circumstance::Circumstance(std::string name) {
	for (int i = 0; i < name.size() && i < 256; i++)
		this->name[i] = name[i];
	for (int i = (int)name.size(); i < 256; i++)
		this->name[i] = ' ';
}
std::string Circumstance::getName() const {
	return std::string(name);
}
unitHelpers::ModernPowerCoef ModernCircumstance::getPowerChanges() const {
	return powerChanges;
}
ModernCircumstance::ModernCircumstance(unitHelpers::ModernPowerCoef& powerChanges, std::string name):Circumstance(name)  {
	this->powerChanges = powerChanges;
}
void ModernCircumstance::setPowerChanges(unitHelpers::ModernPowerCoef& powerChanges) {
	this->powerChanges = powerChanges;
}
void ModernCircumstance::setPowerChanges(unitHelpers::ModernPowerCoef powerChanges) {
	this->powerChanges = powerChanges;
}
