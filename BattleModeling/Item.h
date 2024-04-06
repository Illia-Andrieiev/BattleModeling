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
	modern::ModernPowerCoef powerCoefChanges; /// Multiply unit`s powerCoef. Parameters cannot be < 0
	double changeViability; /// Add to unit`s viability. Can be < 0
	double changeBasePower; /// Add to unit`s base power. Can be < 0
	bool isApplied;
public:
	void apply();
	Item(modern::ModernPowerCoef& powerChanges, char name[256], double changeViability, double changeBasePower);
	modern::ModernPowerCoef getPowerChanges() const;
	double getBasePowerChanges() const;
	double getViabilityChanges() const;
	bool isApply() const;
};

