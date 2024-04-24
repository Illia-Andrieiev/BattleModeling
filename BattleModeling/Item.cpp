#include "Item.h"
#include <stdexcept>
///Constructor
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
/// Set isApplied true
void Item::apply() {
	isApplied = true;
}
/// Get base power changes 
double Item::getBasePowerChanges() const {
	return changeBasePower;
}
/// Get viability changes 
double Item::getViabilityChanges() const {
	return changeViability;
}
/// Return isApplied
bool Item::isApply() const {
	return isApplied;
}
/// Return string interpretation of Item 
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
/// Return is this item equal to other
bool Item::isEqual(const Item& other) const{
	return this->changeBasePower == other.changeBasePower && this->changeViability == other.changeViability &&
		this->isApplied == other.isApplied && std::string(this->name) == std::string(other.name) &&
		isMapsEqual(this->powerCoefChanges, other.powerCoefChanges);
}
/// Is two maps equal
bool Item::isMapsEqual(std::map<unitHelpers::unitTypes, double> map1, std::map<unitHelpers::unitTypes, double> map2) const{
	bool res = true;
	for (auto& pair : map1) {
		res = map1.at(pair.first) == map2.at(pair.first);
		if (!res)
			return false;
	}
	for (auto& pair : map2) {
		try {
			res = map1.at(pair.first) == map2.at(pair.first);
			if (!res)
				return false;
		}
		catch (const std::out_of_range& ) {
			return false;
		}
	}
	return true;
}