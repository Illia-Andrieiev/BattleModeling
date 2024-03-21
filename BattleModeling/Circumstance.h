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
	double powerChanges; /// multiply to unit`s power. Parameters cannot be < 0
public:
	Circumstance(double powerChanges, std::string name);
	std::string getName() const;
	double getPowerChanges() const;
};

