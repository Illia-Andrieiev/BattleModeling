#include "ModernArmy.h"
#include<thread>
ModernArmy::ModernArmy():fortification(Unit(std::string("fortification"), 0, 0)) {
	for (int i = 0; i < 4; i++)
		positionOfFirstAlive[i] = -1;
	power = ModernPowerCoef(0, 0, 0, 0);
	viability = countViability();
	supplies = 0;
}
ModernArmy::ModernArmy(Unit& fortification):fortification(fortification){
	for (int i = 0; i < 4; i++)
		positionOfFirstAlive[i] = -1;
	power = ModernPowerCoef(0, 0, 0, 0);
	viability = countViability();
	supplies = 0;
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
void ModernArmy::attackType(ModernArmy& army,std::vector<ModernUnit>& type, int posFirstAlive) {
	mt.lock();
	if (posFirstAlive != -1) {
		for (int i = posFirstAlive; i < type.size(); i++) {
			type[i].attackArmy(army, supplies);
		}
	}
	mt.unlock();
}
void ModernArmy::attackArmy(ModernArmy& army) {
	std::thread avi([&]() {attackType(army, aviation, positionOfFirstAlive[0]); });
	std::thread veh([&]() {attackType(army, vehickles, positionOfFirstAlive[1]); });
	std::thread inf([&]() {attackType(army, infantry, positionOfFirstAlive[2]); });
	attackType(army, artilery, positionOfFirstAlive[3]);
	avi.join();
	veh.join();
	inf.join();
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
double ModernArmy::getViability() const{
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
ModernArmy& ModernArmy::operator =(const ModernArmy& army) {
	if (this == &army)
		return *this;
	artilery = army.artilery;
	aviation = army.aviation;
	fortification = army.fortification;
	vehickles = army.vehickles;
	infantry = army.infantry;
	viability = army.viability;
	power = army.power;
	positionOfFirstAlive[0] = army.positionOfFirstAlive[0];
	positionOfFirstAlive[1] = army.positionOfFirstAlive[1];
	positionOfFirstAlive[2] = army.positionOfFirstAlive[2];
	positionOfFirstAlive[3] = army.positionOfFirstAlive[3];
	return *this;
}
double ModernArmy::getSupplies() const{
	return supplies;
}
void ModernArmy::changeSupplies(double supply) {
	supplies += supply;
	if (supplies < 0)
		supplies = 0;
}
void ModernArmy::applyItems() {
	for (ModernUnit unit : aviation) {
		unit.applyItems();
	}
	for (ModernUnit unit : artilery) {
		unit.applyItems();
	}
	for (ModernUnit unit : infantry) {
		unit.applyItems();
	}
	for (ModernUnit unit : vehickles) {
		unit.applyItems();
	}
}