#pragma once
#include"Item.h"
#include"UnitHelpers.h"
/// Represent different circumstances, that influent on armies 
/*!
* Change unit`s power once on modeling start. multiply powerChanges with the unit's power. Can increase or decrease.
*/
class Circumstance
{
	char name[256]; /// Circumstance name
public:
	Circumstance(std::string name);
	std::string getName() const;
};

class ModernCircumstance : public Circumstance
{
	unitHelpers::ModernPowerCoef powerChanges;/// multiply to unit`s power. Parameters cannot be < 0
public:
	ModernCircumstance(unitHelpers::ModernPowerCoef& powerChanges, std::string name);
	unitHelpers::ModernPowerCoef getPowerChanges() const;
	void setPowerChanges(unitHelpers::ModernPowerCoef& powerChanges);
	void setPowerChanges(unitHelpers::ModernPowerCoef powerChanges);
};

