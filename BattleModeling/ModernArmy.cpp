#include "ModernArmy.h"
#include<typeinfo>
ModernArmy::ModernArmy():fortification(Unit(std::string("fortification"), 0, 0)) {
	for (int i = 0; i < 4; i++)
		positionOfFirstAlive[i] = -1;
	power = ModernPowerCoef(0, 0, 0, 0);
}
void ModernArmy::countPower() {
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
void ModernArmy::addUnit(ModernUnit& unit, modernUnitTypes type) {
	if (type == modernUnitTypes::infantry) {
		infantry.push_back(unit);
		if (positionOfFirstAlive[2] == -1)
			positionOfFirstAlive[2] = aviation.size() - 1;
	}
	if (type == modernUnitTypes::artilery) {
		artilery.push_back(unit);
		if (positionOfFirstAlive[3] == -1)
			positionOfFirstAlive[3] = aviation.size() - 1;
	}
	if (type == modernUnitTypes::aviation) {
		aviation.push_back(unit);
		if (positionOfFirstAlive[0] == -1)
			positionOfFirstAlive[0] = aviation.size() - 1;
	}
	if (type == modernUnitTypes::armoredVehickle) {
		vehickles.push_back(unit);
		if (positionOfFirstAlive[1] == -1)
			positionOfFirstAlive[1] = aviation.size() - 1;
	}
}

void ModernArmy::attackArmy(ModernArmy& army) {
	
}