#include "Army.h"
#include<thread>
#include <omp.h>
///Constructor
Army::Army(){
	viability = countViability();
	supplies = 0;
	fortification = new Unit();
}
///Constructor
Army::Army(Unit& fortification){
	this->fortification = fortification.clone();
	viability = countViability();
	supplies = 0;
}
/// Copyconstructor
Army::Army(const Army& army){
	for (int i = 0; i < army.units.size(); i++) {
		for (int j = 0; j < army.units[i].size(); j++) {
			addUnit(*army.units[i][j]->clone(),1);
		}
	}
	for (int i = 0; i < 256; i++)
		name[i] = army.name[i];
	fortification = army.fortification->clone();
	viability = army.viability;
	power = army.power;
	supplies = army.supplies;
}
/// Destructor
Army::~Army() {
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			delete units[i][j];
		}
	}
	delete fortification;
}
Army& Army::operator =(const Army& army) {
	if (this == &army)
		return *this;

	for (int i = 0; i < army.units.size(); i++) {
		for (int j = 0; j < army.units[i].size(); j++) {
			addUnit(*(army.units[i][j]->clone()), 1);
		}
	}
	for (int i = 0; i < 256; i++)
		name[i] = army.name[i];
	fortification = army.fortification->clone();
	viability = army.viability;
	power = army.power;
	supplies = army.supplies;
	return *this;
}
/// Set name
void Army::setName(const std::string& name) {
	for (int i = 0; i < 256 && i < name.size(); i++)
		this->name[i] = name[i];
}
/// Summ of average power * damageCoef of every unit in army  
void Army::countPower() {
	power.clear();
	for (int i = 0; i < units.size(); i++) {
		power[units[i][0]->type] = 0;
	}
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			for (int k = 0; k < units.size(); k++) {
				power[units[k][0]->type] += (units[i][j]->maxPower + units[i][j]->minPower) / 2 * units[i][j]->powerCoef[units[k][0]->type];
			}
		}
	}
}
/// Add amount units to army 
void Army::addUnit(Unit& unit, int amount) {
	for (int i = 0; i < units.size(); i++) {
		if (units[i].size() > 0 && units[i][0]->type == unit.type) { ///< Find vector to insert
			while (amount > 0) { 
				--amount;
				units[i].push_back(unit.clone()); ///< Add unit to army
				if (!unit.isAlive()) { ///< If unit dead
					if (positionOfFirstAlive[i] != -1) { ///< If position of firs alive unit != -1
						std::swap(units[i][positionOfFirstAlive[i]], units[i][units[i].size() - 1]);///< swap dead unit and first alive
						positionOfFirstAlive[i]++; ///< increase position of last alive
					}
				}
				else { ///< If unit alive
					if (positionOfFirstAlive[i] == -1)
						positionOfFirstAlive[i] = (int)units[i].size() - 1; ///< Set position of first alive as size-1
				}
			}
			return;
		}
	}
	///< If vector do not exists - create new, and add in him
	units.push_back(std::vector<Unit*>());
	unitTypesPositions[unit.type] = (int)units.size() - 1;
	if (unit.isAlive()) {
		positionOfFirstAlive.push_back(0);
	}else {
		positionOfFirstAlive.push_back(-1);
	}
	while (amount > 0) {
		units[units.size() - 1].push_back(unit.clone());
		--amount;
	}
}
/// Every units in vector attack foes army
void Army::attackType(Army& army, std::vector<Unit*>& type, int posFirstAlive) {
	if (posFirstAlive != -1) {
		for (int i = posFirstAlive; i < type.size(); i++) {
			mt.lock();
			type[i]->attackArmy(army, supplies); ///< Attack army
			mt.unlock();
		}
	}
}
/// Attack another army
void Army::attackArmy(Army& army) {
	std::vector<std::thread> threads;
	for (int i = 0; i < units.size(); ++i)
	{
		threads.push_back(std::thread([&,i]()
			{ attackType(army, units[i], positionOfFirstAlive[i]); })); ///< For each unit`s type vector create thread and attack foe army
	}
	for (auto& thread : threads)
	{
		thread.join();
	}
}
/// Return string interpretation of Army
std::string Army::toString() {
	std::string res = "Name: " + std::string(name);
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			res += (units[i][j]->toString() + " " + std::to_string(j) + "\n");
		}
	}
	res += " power: ";
	for (auto& param : power) {
		res = res + "{" + std::to_string(param.first) + ", " + std::to_string(param.second) + "}; ";
	}
	res += "viability: " + std::to_string(viability);
	res += " fortification: " +fortification->toString();
	return res;
}
/// Return viability
double Army::getViability() const{
	return viability;
}
/// Count summ viability of all units
double Army::countViability() {
	viability = 0;
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			viability += units[i][j]->viability;
		}
	}
	this->viability = viability;
	return viability;
}
/// Return army supplies
double Army::getSupplies() const{
	return supplies;
}
/// Add supplies to current army`s supplies
void Army::changeSupplies(double supply) {
	supplies += supply;
	if (supplies < 0)
		supplies = 0;
}
/// Apply items for every unit
void Army::applyItems() {
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			units[i][j]->applyItems();
		}
	}
}
/// Apply circumstances for armies by multiplying theirs power by special koef 
void Army::applyCircumstance(const Circumstance& circ) {
	for (int i = 0; i < units.size(); i++) {
		if (units[i].size() < 1)
			continue;
		try {
			double koef = circ.getPowerChanges().at(units[i][0]->type);
			for (int j = 0; j < units[i].size(); j++) {
				units[i][j]->multiplyPower(koef);
			}
		}
		catch (const std::out_of_range&) {}
	}
}
/// Sort vector of units by placing equal units alongside
void Army::sortType(std::vector<Unit*>& units) {
	for (int i = 0; i < units.size() - 1; i++) {
		int cur = i+1;
		int j = i+1;
		while (j < units.size() && units[i]->isEqual(units[j])) {
			++i;
			++j;
			++cur;
		}
		for (; j < units.size(); j++) {
			if (units[i]->isEqual(units[j])) {		
				std::swap(units[cur], units[j]);
				++cur;
			}
		}
	}
}
/// Sort all vector of units by placing equal units alongside
void Army::sort() {
	for (int i = 0; i < units.size(); i++) {
		sortType(units[i]);
	}
}
