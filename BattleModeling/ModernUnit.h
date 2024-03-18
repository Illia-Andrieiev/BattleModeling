#pragma once
#include"Unit.h"
#include"army.h"
#include"UnitHelpers.h"
class ModernUnit:public Unit, public Clonable<typename ModernUnit>
{
	bool fortificationTarget; /// Always attack fortifications first
	Cycling cycling; /// Cycling unit on battlefield
	ModernPowerCoef powerCoef; /// Multiply on default damage to another unit`s types 
public:
	ModernUnit(std::string name, double power, double viability, bool fortificationTarget,
		Cycling cycling, ModernPowerCoef powerCoef);
	ModernUnit(std::string name, double power, double viability, bool fortificationTarget,
		std::vector<Item>& items, Cycling cycling, ModernPowerCoef powerCoef);
	ModernUnit clone() override;
	bool getIsActive() const;
	ModernPowerCoef getPowerCoef() const;
	ModernPowerCoef getTypesPower()const;
	void updateCycle();
	void applyItems() override;
};

