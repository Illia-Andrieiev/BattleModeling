#include "Item.h"
Item::Item(ModernPowerCoef& powerChanges, char name[256], double changeViability) {
	this->powerChanges = powerChanges;
	for (int i = 0; i < 256; i++)
		this->name[i] = name[i];
	this->changeViability = changeViability;
}
/// Return power changes for unit
ModernPowerCoef Item::getPowerChanges() const{
	return powerChanges;
}