#include "Army.h"
#include<thread>
Army::Army(){
	viability = countViability();
	supplies = 0;
	fortification = new Unit();
}
Army::Army(Unit& fortification){
	this->fortification = fortification.clone();
	viability = countViability();
	supplies = 0;
}
Army::Army(const Army& army){
	for (int i = 0; i < army.units.size(); i++) {
		for (int j = 0; j < army.units[i].size(); j++) {
			addUnit(*army.units[i][j]->clone(),1);
		}
	}
	fortification = army.fortification;
	viability = army.viability;
	power = army.power;
	positionOfFirstAlive = army.positionOfFirstAlive;
	supplies = army.supplies;
}
Army& Army::operator =(const Army& army) {
	if (this == &army)
		return *this;
	for (int i = 0; i < army.units.size(); i++) {
		for (int j = 0; j < army.units[i].size(); j++) {
			addUnit(*(army.units[i][j]->clone()), 1);
		}
	}
	fortification = army.fortification->clone();
	viability = army.viability;
	power = army.power;
	positionOfFirstAlive = army.positionOfFirstAlive;
	supplies = army.supplies;
	return *this;
}
void Army::countPower() {
	power.clear();
	for (int i = 0; i < units.size(); i++) {
		if (units[i].size() > 0)
			power[units[i][0]->type] = 0;
		for (int j = 0; j < units[i].size(); j++) {
			power[units[i][0]->type] += units[i][j]->power;
		}
	}
}
void Army::addUnit(Unit& unit, int amount) {
	for (int i = 0; i < units.size(); i++) {
		if (units[i].size() > 0 && units[i][0]->type == unit.type) {
			while (amount > 0) {
				--amount;
				units[i].push_back(unit.clone());
				if (positionOfFirstAlive[i] == -1)
					positionOfFirstAlive[i] = (int)units[i].size() - 1;
			}
			return;
		}
	}
	units.push_back(std::vector<Unit*>());
	positionOfFirstAlive.push_back(0);
	while (amount > 0) {
		units[units.size() - 1].push_back(unit.clone());
		--amount;
	}
}
void Army::attackType(Army& army, std::vector<Unit*>& type, int posFirstAlive) {
	if (posFirstAlive != -1) {
		for (int i = posFirstAlive; i < type.size(); i++) {
			mt.lock();
			type[i]->attackArmy(army, supplies);
			mt.unlock();
		}
	}
}
void Army::attackArmy(Army& army) {
	for (int i = 0; i < units.size(); i++) {
		attackType(army, units[i], positionOfFirstAlive[i]);
	}
	//std::thread avi([&]() {attackType(army, aviation, positionOfFirstAlive[0]); });
	//std::thread veh([&]() {attackType(army, vehickles, positionOfFirstAlive[1]); });
	//std::thread inf([&]() {attackType(army, infantry, positionOfFirstAlive[2]); });
	//attackType(army, artilery, positionOfFirstAlive[3]);
	//avi.join();
	//veh.join();
	//inf.join();
}
std::string Army::toString() {
	std::string res = "";
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			res += (units[i][j]->toString() + " " + std::to_string(i) + "\n");
		}
	}
	return res;
}
double Army::getViability() const{
	return viability;
}
double Army::countViability() {
	viability = 0;
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			viability += units[i][j]->viability;
		}
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
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			units[i][j]->applyItems();
		}
	}
}
void Army::applyCircumstance(const Circumstance& circ) {
	for (int i = 0; i < units.size(); i++) {
		if (units[i].size() < 1)
			continue;
		double koef = circ.getPowerChanges()[units[i][0]->type];
		for (int j = 0; j < units[i].size(); j++) {
			units[i][j]->multiplyPower(koef);
		}
	}
}
Army::~Army() {
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			delete units[i][j];
		}
	}
	delete fortification;
}