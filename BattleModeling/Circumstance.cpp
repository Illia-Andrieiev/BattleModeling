#include "Circumstance.h"
Circumstance::Circumstance(double powerChanges, std::string name) {
	if (powerChanges <= 0)
		powerChanges = 1;
	this->powerChanges = powerChanges;
	for (int i = 0; i < name.size() && i < 256; i++)
		this->name[i] = name[i];
	for (int i = name.size(); i < 256; i++)
		this->name[i] = ' ';
}
std::string Circumstance::getName() const {
	return std::string(name);
}
double Circumstance::getPowerChanges() const {
	return powerChanges;
}