#include "Circumstance.h"
///Constructor
Circumstance::Circumstance(std::map<unitHelpers::unitTypes, double>& powerChanges, std::string name) {
	for (int i = 0; i < name.size() && i < 256; i++)
		this->name[i] = name[i];
	setPowerChanges(powerChanges);
}
///Get circumstance`s name
std::string Circumstance::getName() const {
	return std::string(name);
}
/// Get power changes for units
std::map<unitHelpers::unitTypes, double> Circumstance::getPowerChanges() const {
	return powerChanges;
}
/// Set power changes for units
void Circumstance::setPowerChanges(std::map<unitHelpers::unitTypes, double>& powerChanges) {
	for (auto& param : powerChanges) {
		if (param.second <= 0)
			powerChanges[param.first] = 1;
	}
	this->powerChanges = powerChanges;
}

