#include "Circumstance.h"
#include <stdexcept>
///Constructor
Circumstance::Circumstance(std::map<unitHelpers::unitTypes, double>& powerChanges, std::string name) {
	for (int i = 0; i < name.size() && i < 256; i++)
		this->name[i] = name[i];
	setPowerChanges(powerChanges);
}
std::string Circumstance::toString() {
	std::string res = "powerCoefChanges: ";
	for (auto& param : powerChanges) {
		res = res + "{" + std::to_string(param.first) + ", " + std::to_string(param.second) + "}; ";
	}
	res = res + " name: " + std::string(name);
	return res;
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
/// Is circumstances equal
bool Circumstance::isEqual(const Circumstance& other) const {
	return  std::string(this->name) == std::string(other.name) && isMapsEqual(this->powerChanges, other.powerChanges);
}
/// Is two maps equal
bool Circumstance::isMapsEqual(std::map<unitHelpers::unitTypes, double> map1, std::map<unitHelpers::unitTypes, double> map2) const {
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
		catch (const std::out_of_range&) {
			return false;
		}
	}
	return true;
}
void Circumstance::setName(std::string name) {
	for (int i = 0; i < 256 && i < name.size(); i++)
		this->name[i] = name[i];
}
void Circumstance::setPowerCoef(std::pair<unitHelpers::unitTypes, double> typeCoef) {
	powerChanges[typeCoef.first] = typeCoef.second;
}