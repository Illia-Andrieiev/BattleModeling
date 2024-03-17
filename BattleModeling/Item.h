#pragma once
#include<string>
#include"UnitHelpers.h"
/// Represent items, that can be equiped by units
/*!
* Change unit`s power once on modeling start. adds powerChanges to the unit's power. Can increase or decrease.
*/
class Item
{
private:
	char name[256]; /// Item name
	ModernPowerCoef powerChanges; /// Add to unit`s power. Parameters can be < 0
	double changeViability; /// Add to unit`s viability. Can be < 0
public:
	Item(ModernPowerCoef& powerChanges, char name[256], double changeViability);
	ModernPowerCoef getPowerChanges() const;
};

