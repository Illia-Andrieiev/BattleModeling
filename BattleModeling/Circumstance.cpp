#include "Circumstance.h"
Circumstance::Circumstance(std::map<unitHelpers::unitTypes, double>& powerChanges, std::string name) {
	for (int i = 0; i < name.size() && i < 256; i++)
		this->name[i] = name[i];
	setPowerChanges(powerChanges);
}
std::string Circumstance::getName() const {
	return std::string(name);
}
std::map<unitHelpers::unitTypes, double> Circumstance::getPowerChanges() const {
	return powerChanges;
}

void Circumstance::setPowerChanges(std::map<unitHelpers::unitTypes, double>& powerChanges) {
	for (auto& param : powerChanges) {
		if (param.second < 0)
			powerChanges[param.first] = 0;
	}
	this->powerChanges = powerChanges;
}

