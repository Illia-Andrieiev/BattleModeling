#include "Item.h"
Item::Item(Power& powerChanges, char name[256], double changeViability) {
	this->powerChanges = powerChanges;
	for (int i = 0; i < 256; i++)
		this->name[i] = name[i];
	this->changeViability = changeViability;
}
/// Return power changes for unit
Power Item::getPowerChanges() const{
	return powerChanges;
}