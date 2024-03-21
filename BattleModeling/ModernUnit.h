#pragma once
#include"Unit.h"
#include"ModernArmy.h"
#include"UnitHelpers.h"
class ModernArmy;
class ModernUnit:public Unit, public Clonable<typename ModernUnit>
{
	friend ModernArmy;
	bool fortificationTarget; /// Always attack fortifications first
	Cycling cycling; /// Cycling unit on battlefield
	ModernPowerCoef powerCoef; /// Multiply on default damage to another unit`s types 
	modernUnitTypes chooseTarget(ModernArmy& army) const;
	int chooseTargetNomer(std::vector<ModernUnit>& units, int firstAlive);
	void attackFortification(Unit& fortification, double& damage);
	void attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<ModernUnit>& units);
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
	void attackArmy(ModernArmy& army, double& supplies);
};

