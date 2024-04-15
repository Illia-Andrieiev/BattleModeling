#include "Item.h"
Item::Item(std::map<unitHelpers::unitTypes, double>& powerChanges, char name[256], double changeViability, double changeBasePower) {
	for (auto& param : powerChanges) {
		if (param.second < 0)
			powerChanges[param.first] = 0;
	}
	this->powerCoefChanges = powerChanges;
	this->changeBasePower = changeBasePower;
	for (int i = 0; i < 256; i++)
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