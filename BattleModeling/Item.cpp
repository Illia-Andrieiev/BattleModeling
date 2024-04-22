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
bool Item::isEqual(const Item& other) const{
	return this->changeBasePower == other.changeBasePower && this->changeViability == other.changeViability &&
		this->isApplied == other.isApplied && std::string(this->name) == std::string(other.name) &&
		isMapsEqual(this->powerCoefChanges, other.powerCoefChanges);
}
bool Item::isMapsEqual(std::map<unitHelpers::unitTypes, double> map1, std::map<unitHelpers::unitTypes, double> map2) const{
	bool res = true;
	for (auto& pair : map1) {
		res = map1.at(pair.first) == map2.at(pair.first);
		if (!res)
			return false;
	}
	for (auto& pair : map2) {
		res = map1.at(pair.first) == map2.at(pair.first);
		if (!res)
			return false;
	}
	return true;
}