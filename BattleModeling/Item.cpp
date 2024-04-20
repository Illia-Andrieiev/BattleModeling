#include "Item.h"
Item::Item(std::map<unitHelpers::unitTypes, double>& powerChanges, const std::string& name, double changeViability, double changeBasePower) {
	for (auto& param : powerChanges) {
		if (param.second < 0)
			powerChanges[param.first] = 0;
	}
	this->powerCoefChanges = powerChanges;
	this->changeBasePower = changeBasePower;
	for (int i = 0; i < 256 && i<name.size(); i++)
		this->name[i] = name[i];
	this->changeViability = changeViability;
	isApplied = false;
}
/// Return power changes for unit
std::map<unitHelpers::unitTypes, double> Item::getPowerChanges() const{
	return powerCoefChanges;
}
void Item::apply() {
	isApplied = true;
}
double Item::getBasePowerChanges() const {
	return changeBasePower;
}
double Item::getViabilityChanges() const {
	return changeViability;
}
bool Item::isApply() const {
	return isApplied;
}
std::string Item::toString() {
	std::string res = "powerCoefChanges: ";
	for (auto& param : powerCoefChanges) {
		res = res + "{" + std::to_string(param.first) + ", " +std::to_string(param.second) + "}; ";
	}
	res = res + " name: " + std::string(name);
	res = res + " viability changes: " + std::to_string(changeViability) + " power changes: " + std::to_string(changeBasePower)
		+ " is applied: " + std::to_string(isApplied);
	return res;
}