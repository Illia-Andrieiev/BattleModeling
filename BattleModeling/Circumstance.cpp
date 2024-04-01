#include "Circumstance.h"
Circumstance::Circumstance(std::string name) {
	for (int i = 0; i < name.size() && i < 256; i++)
		this->name[i] = name[i];
	for (int i = name.size(); i < 256; i++)
		this->name[i] = ' ';
}
std::string Circumstance::getName() const {
	return std::string(name);
}
modern::ModernPowerCoef ModernCircumstance::getPowerChanges() const {
	return powerChanges;
}
ModernCircumstance::ModernCircumstance(modern::ModernPowerCoef& powerChanges, std::string name):Circumstance(name)  {
	this->powerChanges = powerChanges;
}
void ModernCircumstance::setPowerChanges(modern::ModernPowerCoef& powerChanges) {
	this->powerChanges = powerChanges;
}
void ModernCircumstance::setPowerChanges(modern::ModernPowerCoef powerChanges) {
	this->powerChanges = powerChanges;
}
