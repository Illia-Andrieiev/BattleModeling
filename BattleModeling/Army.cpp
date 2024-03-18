#include "Army.h"
#include<typeinfo>
Army::Army():fortification(Unit(std::string("fortification"), 0, 0)) {
	for (int i = 0; i < 4; i++)
		positionOfLastAlive[i] = -1;
	power = ModernPowerCoef(0, 0, 0, 0);
}
void Army::countPower() {
	for (ModernUnit unit : aviation) {
		ModernPowerCoef unitPower = unit.getTypesPower();
		power = power + unitPower;
	}
	for (ModernUnit unit : artilery) {
		ModernPowerCoef unitPower = unit.getTypesPower();
		power = power + unitPower;

	}
	for (ModernUnit unit : infantry) {
		ModernPowerCoef unitPower = unit.getTypesPower();
		power = power + unitPower;
	}
	for (ModernUnit unit : vehickles) {
		ModernPowerCoef unitPower = unit.getTypesPower();
		power = power + unitPower;
	}
}
void Army::addUnit(ModernUnit& unit, modernUnitTypes type) {
	if (type == modernUnitTypes::infantry) {
		infantry.push_back(unit);
	}
	if (type == modernUnitTypes::artilery) {
		artilery.push_back(unit);
	}
	if (type == modernUnitTypes::aviation) {
		aviation.push_back(unit);
	}
	if (type == modernUnitTypes::armoredVehickle) {
		vehickles.push_back(unit);
	}
}