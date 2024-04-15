#include "Army.h"
#include<thread>
Army::Army(){
	power = unitHelpers::ModernPowerCoef(0, 0, 0, 0);
	viability = countViability();
	supplies = 0;
}
Army::Army(const Unit& fortification){
	this->fortification = fortification;
	power = unitHelpers::ModernPowerCoef(0, 0, 0, 0);
	viability = countViability();
	supplies = 0;
}
Army::Army(const Army& army){
	units = army.units;
	fortification = army.fortification;
	viability = army.viability;
	power = army.power;
	positionOfFirstAlive = army.positionOfFirstAlive;
	supplies = army.supplies;
}
Army& Army::operator =(const Army& army) {
	if (this == &army)
		return *this;
	units = army.units;
	fortification = army.fortification;
	viability = army.viability;
	power = army.power;
	positionOfFirstAlive = army.positionOfFirstAlive;
	supplies = army.supplies;
	return *this;
}
void Army::countPower() {
	power = unitHelpers::ModernPowerCoef(0, 0, 0, 0);
	for (ModernUnit unit : aviation) {
		unitHelpers::ModernPowerCoef unitPower = unit.getTypesPower();
		power = power + unitPower;
	}
	for (ModernUnit unit : artilery) {
		unitHelpers::ModernPowerCoef unitPower = unit.getTypesPower();
		power = power + unitPower;

	}
	for (ModernUnit unit : infantry) {
		unitHelpers::ModernPowerCoef unitPower = unit.getTypesPower();
		power = power + unitPower;
	}
	for (ModernUnit unit : vehickles) {
		unitHelpers::ModernPowerCoef unitPower = unit.getTypesPower();
		power = power + unitPower;
	}
}
void Army::addUnit(const ModernUnit& unit, unitHelpers::unitTypes type) {
	if (type == unitHelpers::unitTypes::infantry) {
		infantry.push_back(unit);
		if (positionOfFirstAlive[2] == -1)
			positionOfFirstAlive[2] = (int)infantry.size() - 1;
	}
	if (type == unitHelpers::unitTypes::artilery) {
		artilery.push_back(unit);
		if (positionOfFirstAlive[3] == -1)
			positionOfFirstAlive[3] = (int)artilery.size() - 1;
	}
	if (type == unitHelpers::unitTypes::aviation) {
		aviation.push_back(unit);
		if (positionOfFirstAlive[0] == -1)
			positionOfFirstAlive[0] = (int)aviation.size() - 1;
	}
	if (type == unitHelpers::unitTypes::armoredVehickle) {
		vehickles.push_back(unit);
		if (positionOfFirstAlive[1] == -1)
			positionOfFirstAlive[1] = (int)vehickles.size() - 1;
	}
}
void Army::attackType(Army& army,std::vector<ModernUnit>& type, int posFirstAlive) {
	if (posFirstAlive != -1) {
		for (int i = posFirstAlive; i < type.size(); i++) {
			mt.lock();
			type[i].attackArmy(army, supplies);
			mt.unlock();
		}
	}
}
void Army::attackArmy(Army& army) {
	std::thread avi([&]() {attackType(army, aviation, positionOfFirstAlive[0]); });
	std::thread veh([&]() {attackType(army, vehickles, positionOfFirstAlive[1]); });
	std::thread inf([&]() {attackType(army, infantry, positionOfFirstAlive[2]); });
	attackType(army, artilery, positionOfFirstAlive[3]);
	avi.join();
	veh.join();
	inf.join();
}
std::string Army::toString() {
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
double Army::getViability() const{
	return viability;
}
double Army::countViability() {
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

double Army::getSupplies() const{
	return supplies;
}
void Army::changeSupplies(double supply) {
	supplies += supply;
	if (supplies < 0)
		supplies = 0;
}
void Army::applyItems() {
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
void Army::applyCircumstance(const ModernCircumstance& circ) {
	for (int i = 0; i < infantry.size(); i++) {
		infantry[i].multiplyPower(circ.getPowerChanges().infantryDamagekoef);
	}
	for (int i = 0; i < aviation.size(); i++) {
		aviation[i].multiplyPower(circ.getPowerChanges().aviationDamagekoef);
	}
	for (int i = 0; i < vehickles.size(); i++) {
		vehickles[i].multiplyPower(circ.getPowerChanges().vehickleDamagekoef);
	}
	for (int i = 0; i < artilery.size(); i++) {
		artilery[i].multiplyPower(circ.getPowerChanges().artileryDamagekoef);
	}
}
Army Army::clone() {
	Army army;
	army.artilery = artilery;
	army.aviation = aviation;
	army.fortification = fortification;
	army.vehickles = vehickles;
	army.infantry = infantry;
	army.viability = viability;
	power = army.power;
	army.positionOfFirstAlive[0] = positionOfFirstAlive[0];
	army.positionOfFirstAlive[1] = positionOfFirstAlive[1];
	army.positionOfFirstAlive[2] = positionOfFirstAlive[2];
	army.positionOfFirstAlive[3] = positionOfFirstAlive[3];
	army.supplies = supplies;
	return army;
}
Army::~Army() {
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			delete units[i][j];
		}
	}
}