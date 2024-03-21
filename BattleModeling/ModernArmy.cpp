#include "ModernArmy.h"
#include<thread>
ModernArmy::ModernArmy():fortification(Unit(std::string("fortification"), 0, 0)) {
	for (int i = 0; i < 4; i++)
		positionOfFirstAlive[i] = -1;
	power = ModernPowerCoef(0, 0, 0, 0);
	viability = countViability();
}
void ModernArmy::countPower() {
	power = ModernPowerCoef(0, 0, 0, 0);
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
			positionOfFirstAlive[2] = (int)infantry.size() - 1;
	}
	if (type == modernUnitTypes::artilery) {
		artilery.push_back(unit);
		if (positionOfFirstAlive[3] == -1)
			positionOfFirstAlive[3] = (int)artilery.size() - 1;
	}
	if (type == modernUnitTypes::aviation) {
		aviation.push_back(unit);
		if (positionOfFirstAlive[0] == -1)
			positionOfFirstAlive[0] = (int)aviation.size() - 1;
	}
	if (type == modernUnitTypes::armoredVehickle) {
		vehickles.push_back(unit);
		if (positionOfFirstAlive[1] == -1)
			positionOfFirstAlive[1] = (int)vehickles.size() - 1;
	}
}
std::mutex mut;
void ModernArmy::attackType(ModernArmy& army,std::vector<ModernUnit>& type, int posFirstAlive) {
	mut.lock();
	if (posFirstAlive != -1) {
		for (int i = posFirstAlive; i < type.size(); i++) {
			type[i].attackArmy(army);
		}
	}
	mut.unlock();
}
void ModernArmy::attackArmy(ModernArmy& army) {
	attackType(army, aviation, positionOfFirstAlive[0]);  
	attackType(army, vehickles, positionOfFirstAlive[1]); 
	attackType(army, infantry, positionOfFirstAlive[2]); 
	attackType(army, artilery, positionOfFirstAlive[3]);
}
std::string ModernArmy::toString() {
	std::string res = "";
	for (int i = 0; i < aviation.size(); i++) {
		res += (aviation[i].toString() + " " + std::to_string(i) + "\n");
	}
	for (int i = 0; i < artilery.size(); i++) {
		res += (artilery[i].toString() + " " + std::to_string(i) + "\n");
	}
	for (int i = 0; i < infantry.size(); i++) {
		res += (infantry[i].toString() + " " + std::to_string(i) + "\n");
	}
	for (int i = 0; i < vehickles.size(); i++) {
		res += (vehickles[i].toString() + " " + std::to_string(i) + "\n");
	}
	return res;
}
double ModernArmy::getViability() {
	return viability;
}
double ModernArmy::countViability() {
	viability = 0;
	for (ModernUnit unit : aviation) {
		viability += unit.getViability();
	}
	for (ModernUnit unit : artilery) {
		viability += unit.getViability();
	}
	for (ModernUnit unit : infantry) {
		viability += unit.getViability();
	}
	for (ModernUnit unit : vehickles) {
		viability += unit.getViability();
	}
	return viability;
}