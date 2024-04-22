#pragma once
#include<string>
#include<map>
#include"UnitHelpers.h"
/// Represent items, that can be equiped by units
/*!
* Change unit`s power once on modeling start. adds powerChanges to the unit's power. Can increase or decrease.
*/
class Item
{
	friend class FileManager;
private:
	char name[256]; /// Item name
	std::map<unitHelpers::unitTypes, double> powerCoefChanges; /// Multiply unit`s powerCoef. Parameters cannot be < 0
	double changeViability; /// Add to unit`s viability. Can be < 0
	double changeBasePower; /// Add to unit`s base power. Can be < 0
	bool isApplied;
	bool isMapsEqual(std::map<unitHelpers::unitTypes, double> map1, std::map<unitHelpers::unitTypes, double> map2) const;
public:
	void apply();
	bool isEqual(const Item& other) const;
	Item(std::map<unitHelpers::unitTypes, double>& powerChanges, const std::string& name, double changeViability, double changeBasePower);
	std::map<unitHelpers::unitTypes, double> getPowerChanges() const;
	double getBasePowerChanges() const;
	double getViabilityChanges() const;
	bool isApply() const;
	std::string toString();
};

