#pragma once
#include"Unit.h"
#include"ModernArmy.h"
#include"UnitHelpers.h"

class ModernUnit:public Unit 
{

public:
	ModernUnit(std::string name, double power, double viability, bool fortificationTarget,
		unitHelpers::Cycling cycling, unitHelpers::ModernPowerCoef powerCoef);
	ModernUnit(std::string name, double power, double viability, bool fortificationTarget,
		std::vector<Item>& items, unitHelpers::Cycling cycling, unitHelpers::ModernPowerCoef powerCoef);
};