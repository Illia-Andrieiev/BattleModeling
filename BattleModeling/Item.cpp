#include "Item.h"
Item::Item(modern::ModernPowerCoef& powerChanges, char name[256], double changeViability, double changeBasePower) {
	if (powerChanges.artileryDamagekoef < 0)
		powerChanges.artileryDamagekoef = 0;
	if (powerChanges.aviationDamagekoef < 0)
		powerChanges.aviationDamagekoef = 0;
	if (powerChanges.vehickleDamagekoef < 0)
		powerChanges.vehickleDamagekoef = 0;
	if (powerChanges.infantryDamagekoef < 0)
		powerChanges.infantryDamagekoef = 0;
	this->powerCoefChanges = powerChanges;
	this->changeBasePower = changeBasePower;
	for (int i = 0; i < 256; i++)
		this->name[i] = name[i];
	this->changeViability = changeViability;
	isApplied = false;
}
/// Return power changes for unit
modern::ModernPowerCoef Item::getPowerChanges() const{
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