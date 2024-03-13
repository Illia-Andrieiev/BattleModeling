#include "Army.h"
#include<typeinfo>
Army::Army() {
	for (int i = 0; i < 4; i++)
		positionOfLastAlive[i] = -1;
}
Army::Army(std::vector<Unit> units) {
	for (int i = 0; i < 4; i++)
		positionOfLastAlive[i] = -1;
	for (Unit unit : units)
		addUnit(unit);
}
double Army::countPower() {
	for (Unit unit : aviation) {
		if (unit.isAlive()) {
			Power unitPower = unit.getPower();
			power = power + unitPower;
		}
	}
	for (Unit unit : artilery) {
		if (unit.isAlive()) {
			Power unitPower = unit.getPower();
			power = power + unitPower;
		}
	}
	for (Unit unit : vehickles) {
		if (unit.isAlive()) {
			Power unitPower = unit.getPower();
			power = power + unitPower;
		}
	}
	for (Unit unit : infantry) {
		if (unit.isAlive()) {
			Power unitPower = unit.getPower();
			power = power + unitPower;
		}
	}
}
void Army::addUnit(Unit unit) {
	if (typeid(unit).name() == typeid(Aviation).name()) {
		aviation.push_back(unit);
	}
	if (typeid(unit).name() == typeid(Artilery).name()) {

	}
	if (typeid(unit).name() == typeid(Infantry).name()) {

	}
	else {
		artilery.push_back(unit);
	}
}