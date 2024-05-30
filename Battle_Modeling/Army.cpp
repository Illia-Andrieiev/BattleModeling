#include "Army.h"
#include<thread>
#include <tbb/tbb.h>
#include"MoralUnit.h"
#include <chrono>
//#define ISBENCHMARK true;
///Constructor
Army::Army() {
	viability = countViability();
	supplies = 0;
	fortification = new Unit();
}
///Constructor
Army::Army(Unit& fortification) {
	this->fortification = fortification.clone();
	viability = countViability();
	supplies = 0;
}
/// Copyconstructor
Army::Army(const Army& army) {
	for (int i = 0; i < army.units.size(); i++) {
		for (int j = 0; j < army.units[i].size(); j++) {
			addUnit(*army.units[i][j]->clone(), 1);
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
	for (auto& u : units) {
		for (auto& uun : u)
			delete uun;
	}
	units.clear();
	unitTypesPositions.clear();
	positionOfFirstAlive.clear();
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

void Army::setFortification(Unit& unit) {
	delete fortification;
	fortification = unit.clone();
}
Unit Army::getFortification() {
	return *fortification;
}
/// Add amount units to army 
void Army::addUnit(Unit& unit, int amount) {
	if (amount <= 0)
		return;
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
	}
	else {
		positionOfFirstAlive.push_back(-1);
	}
	while (amount > 0) {
		units[units.size() - 1].push_back(unit.clone());
		--amount;
	}
}
/// Class for attackType thread pool. Used as functor
class ApplyAttackType {
	std::vector<Unit*>& units;
	Army& army;
	double& sup;
public:
	void operator()(const tbb::blocked_range<size_t>& r) const {
		std::vector<Unit*>& newUnits = units;
		for (size_t i = r.begin(); i != r.end(); ++i)
			units[i]->attackArmy(army, sup);
	}
	ApplyAttackType(std::vector<Unit*>& units, Army& army, double& sup) :
		units(units), army(army), sup(sup)
	{}
};
/// Every units in vector attack foes army
void Army::attackType(Army& army, std::vector<Unit*>& type, int posFirstAlive) {
	if (posFirstAlive != -1) {
		//AttackFunctor f;
#ifdef ISBENCHMARK
		int threadAmount = 2;
		tbb::task_arena limited_arena(threadAmount); // init task area
		// for every type call attackType method in new thread in thread pool
		limited_arena.execute([&] {
			tbb::parallel_for(tbb::blocked_range<std::size_t>(posFirstAlive, type.size()), ApplyAttackType(type, army, supplies));
			});
		
#endif
#ifndef ISBENCHMARK
		// for every unit call attackType method in new thread in thread pool
		tbb::parallel_for(tbb::blocked_range<std::size_t>(posFirstAlive, type.size()), ApplyAttackType(type, army, supplies));
#endif
		
	}
}
/// Class for attackArmy thread pool. Used as functor
class ApplyAttackArmy {
	std::vector<std::vector<Unit*>>& units;
	Army& elseArmy;
	Army* thisArmy;
	std::vector<int>& posFirstAlive;
public:
	void operator()(const tbb::blocked_range<size_t>& r) const {
		for (size_t i = r.begin(); i != r.end(); ++i)
			thisArmy->attackType(elseArmy, units[i], posFirstAlive[i]);
	}
	ApplyAttackArmy(std::vector<std::vector<Unit*>>& units,Army* thisArmy ,Army& elseArmy, std::vector<int>& posFirstAlive) :
		units(units), elseArmy(elseArmy), posFirstAlive(posFirstAlive)
	{
		this->thisArmy = thisArmy;
	}
};
/// Attack another army
void Army::attackArmy(Army& army) {
	/* Old realisation
	std::vector<std::thread> threads;
	for (int i = 0; i < units.size(); ++i)
	{
		threads.push_back(std::thread([&, i]()
			{ attackType(army, units[i], positionOfFirstAlive[i]); })); ///< For each unit`s type vector create thread and attack foe army
	}
	for (auto& thread : threads)
	{
		thread.join();
	}
	*/
	if (units.size() == 0)
		return;
#ifdef ISBENCHMARK
	// start counting
	auto start = std::chrono::high_resolution_clock::now();
	int threadAmount = 2;
	tbb::task_arena limited_arena(threadAmount); // init task area

	// for every type call attackType method in new thread in thread pool
	limited_arena.execute([&] {
		tbb::parallel_for(tbb::blocked_range<std::size_t>(0, units.size()), ApplyAttackArmy(units, this, army, positionOfFirstAlive));
});
	// stop counting
	auto end = std::chrono::high_resolution_clock::now();
	// find time
	std::chrono::duration<double> resTime = end - start;
	// log
	//static std::mutex mt;
	//std::lock_guard<std::mutex> guard(mt);
	//std::fstream log;
	//log.open("log_benchmark.txt", std::ios::app | std::ios::in | std::ios::out);
	//log << "Army: " << this->name << " attack time: " << resTime << std::endl;
	//log.close();
#endif
#ifndef ISBENCHMARK
	// for every type call attackType method in new thread in thread pool
	tbb::parallel_for(tbb::blocked_range<std::size_t>(0, units.size()), ApplyAttackArmy(units,this ,army, positionOfFirstAlive));
#endif
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
	res += " fortification: " + fortification->toString();
	return res;
}
/// Return viability
double Army::getViability() const {
	return viability;
}
/// Return power;
std::map<unitHelpers::unitTypes, double> Army::getPower() const {
	return power;
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
double Army::getSupplies() const {
	return supplies;
}
/// Add supplies to current army`s supplies
void Army::changeSupplies(double supply) {
	supplies += supply;
	if (supplies < 0)
		supplies = 0;
}
/// Delete first unit whith that name
bool Army::deleteUnit(std::string name) {
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			if (units[i][j]->getName() == name) {
				if (units[i][j]->isAlive()) {
					if (j == positionOfFirstAlive[i] && j == units[i].size() - 1) {
						positionOfFirstAlive[i] = -1;
					}
					else {
						std::swap(units[i][j], units[i][units[i].size() - 1]);
					}
				}
				else {
					std::swap(units[i][j], units[i][positionOfFirstAlive[i]-1]);
					std::swap(units[i][units[i].size()-1], units[i][positionOfFirstAlive[i]-1]);
					positionOfFirstAlive[i] = positionOfFirstAlive[i] - 1;
				}
				units[i].pop_back();
				if (units[i].size() == 0) {
					std::swap(units[i], units[units.size() - 1]);
					units.pop_back();
					std::swap(positionOfFirstAlive[i], positionOfFirstAlive[positionOfFirstAlive.size() - 1]);
					positionOfFirstAlive.pop_back();
				}
				return true;
			}
		}
	}
	return false;
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
	if (units.size() == 0)
		return;
	for (int i = 0; i < units.size() - 1; i++) {
		int cur = i + 1;
		int j = i + 1;
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
/// Return amount of unique units in army
int Army::getAmountOfUniqueUnits() {
	Army army = *this;
	army.sort();
	int size = 0; ///< Find amount of unique units in army
	for (int i = 0; i < army.units.size(); i++) {
		for (int j = 0; j < army.units[i].size(); j++) {
			while (j + 1 < (int)army.units[i].size() && army.units[i][j]->isEqual(army.units[i][j + 1])) {
				++j;
			}
			++size;
		}
	}
	return size;
}
/// Sort all vector of units by placing equal units alongside
void Army::sort() {
	for (int i = 0; i < units.size(); i++) {
		sortType(units[i]);
	}
}
/// Return true, if units of armies equal and arranged in the same order
bool Army::isUnitsEqual(const Army& other) const {
	if (this->units.size() != other.units.size())
		return false;
	for (int i = 0; i < units.size(); i++) {
		if (this->units[i].size() != other.units[i].size())
			return false;
		for (int j = 0; j < units[i].size(); j++) {
			if (!units[i][j]->isEqual(other.units[i][j]))
				return false;
		}
	}
	return true;
}
/// Return string name
std::string Army::getName() {
	return std::string(name);
}
/// Create memento
std::shared_ptr<MementoArmy> Army::createMemento(int round) {
	return std::make_shared<MementoArmy>(*this, round);
}
/// Reinstate Memento
void Army::reinstateMemento(MementoArmy* memento) {
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++)
			delete units[i][j];
	}
	units.clear();
	unitTypesPositions.clear();
	positionOfFirstAlive.clear();
	for (int i = 0; i < memento->units.size(); i++) {
		for (int j = 0; j < memento->units[i].size(); j++) {
			addUnit(*(memento->units[i][j]->clone()), 1);
		}
	}
	delete fortification;
	fortification = memento->fortification->clone();
	supplies = memento->supplies;
}
/// Reinstate Memento
void Army::reinstateMemento(std::shared_ptr<MementoArmy> memento) {
	reinstateMemento(memento.get());
}
/*
**************************************************
*/
ArmyTest::ArmyTest() {
	std::string namesol("Solider 1");
	unitHelpers::Cycling soliderCycle(10, 2, true);
	std::map<unitHelpers::unitTypes, double> soliderPowerCoef = { {unitHelpers::aviation,0.05}, {unitHelpers::infantry,1},
	{unitHelpers::armoredVehickle,0.15}, {unitHelpers::artilery,0.1} };
	Item item(soliderPowerCoef, "Item name", 313, 31);
	MoralUnitBuilder build;
	build.setCycling(soliderCycle)->setFortificationTarget(false)->setName(namesol)->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
		->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::infantry)->addItem(item)->addItem(item)->setMorality(75.4, 1);
	MoralUnit solider = *std::dynamic_pointer_cast<MoralUnit>(build.getResult());
	build.reset();
	build.setCycling(soliderCycle)->setFortificationTarget(false)->setName("solider 2")->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
		->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::armoredVehickle)->addItem(item);
	Unit solider2 = *build.getResult();
	build.reset();
	build.setCycling(soliderCycle)->setFortificationTarget(true)->setName("solider 3")->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
		->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::armoredVehickle);
	Unit solider3 = *build.getResult();
	build.reset();
	//******************************
	std::string nameavi("F-16");
	unitHelpers::Cycling aviCycle(8, 2, true);
	std::map<unitHelpers::unitTypes, double> aviPowerCoef = { {unitHelpers::aviation,1}, {unitHelpers::infantry,0.2},
	{unitHelpers::armoredVehickle,0.8}, {unitHelpers::artilery,0.8} };
	build.setCycling(aviCycle)->setFortificationTarget(false)->setName(nameavi)->setPowerAndViability(200, 220, 600)->setPowerCoef(aviPowerCoef)
		->setTypes(unitHelpers::unitTypes::aviation, unitHelpers::unitTypes::aviation);
	Unit avi = *build.getResult();
	build.reset();
	//*****************************
	std::string nametank("T-64 Bulat");
	unitHelpers::Cycling tankCycle(12, 1, true);
	std::map<unitHelpers::unitTypes, double> tankPowerCoef = { {unitHelpers::aviation,0.01}, {unitHelpers::infantry,1.3},
	{unitHelpers::armoredVehickle,1.5}, {unitHelpers::artilery,0.5} };
	build.setCycling(tankCycle)->setFortificationTarget(false)->setName(nametank)->setPowerAndViability(150, 200, 600)->setPowerCoef(tankPowerCoef)
		->setTypes(unitHelpers::unitTypes::armoredVehickle, unitHelpers::unitTypes::armoredVehickle);
	Unit tank = *build.getResult();
	build.reset();
	//*******************************
	std::string nameart("Caesar");
	std::string namepatr("Patriot");
	unitHelpers::Cycling artCycle(10, 0, true);
	std::map<unitHelpers::unitTypes, double> artPowerCoef = { {unitHelpers::aviation,0}, {unitHelpers::infantry,1.5},
	{unitHelpers::armoredVehickle,1}, {unitHelpers::artilery,0.8} };
	std::map<unitHelpers::unitTypes, double> patrPowerCoef = { {unitHelpers::aviation,2}, {unitHelpers::infantry,0.2},
	{unitHelpers::armoredVehickle,0.3}, {unitHelpers::artilery,0.3} };
	build.setCycling(artCycle)->setFortificationTarget(false)->setName(nameart)->setPowerAndViability(150, 150, 400)->setPowerCoef(artPowerCoef)
		->setTypes(unitHelpers::unitTypes::artilery, unitHelpers::unitTypes::armoredVehickle);
	Unit art = *build.getResult();
	build.reset();
	build.setCycling(artCycle)->setFortificationTarget(false)->setName(namepatr)->setPowerAndViability(150, 150, 450)->setPowerCoef(patrPowerCoef)
		->setTypes(unitHelpers::unitTypes::artilery, unitHelpers::unitTypes::aviation)->setArmor(12, true);
	Unit patr = *build.getResult();
	build.reset();
	////*********************************************
	army.setName("Army for testing");
	army.changeSupplies(23232);
	army.addUnit(solider, 2);
	army.addUnit(solider2, 2);
	army.addUnit(solider3, 1);
	army.addUnit(solider, 2);
	army.addUnit(solider2, 2);
	army.addUnit(solider3, 1);
	army.addUnit(solider2, 2);
	army.addUnit(solider3, 1);
	army.addUnit(avi, 5);
	army.addUnit(tank, 3);
	army.addUnit(art, 2);
	army.addUnit(patr, 1);
	army.addUnit(art, 2);
	army.addUnit(patr, 1);
	army.addUnit(art, 2);
	army.addUnit(patr, 1);
	sortedArmy.addUnit(solider, 4);
	sortedArmy.addUnit(solider2, 6);
	sortedArmy.addUnit(solider3, 3);
	sortedArmy.addUnit(avi, 5);
	sortedArmy.addUnit(tank, 3);
	sortedArmy.addUnit(art, 6);
	sortedArmy.addUnit(patr, 3);
}
void ArmyTest::sortTest() {
	Army army = this->army;
	using namespace boost::ut;
	"sort"_test = [&] {
		army.sort();
		expect(army.getAmountOfUniqueUnits() == 7);
		Unit u;
		army.addUnit(u, 1);
		expect(army.getAmountOfUniqueUnits() == 8);
		};
}
void ArmyTest::isUitsEqualTest() {
	using namespace boost::ut;
	"isUnitsEqual"_test = [&] {
		expect(!army.isUnitsEqual(sortedArmy));
		expect(army.isUnitsEqual(army));
		};
}
void ArmyTest::getAmountOfUniqueUnitsTest() {
	using namespace boost::ut;
	Army army = this->army;
	"getAmountOfUniqueUnits"_test = [&] {
		expect(army.getAmountOfUniqueUnits() == 7);
		expect(sortedArmy.getAmountOfUniqueUnits() == 7);
		Unit u;
		army.addUnit(u, 3);
		expect(army.getAmountOfUniqueUnits() == 8);
		double dam = 999999;
		u.takeDamage(dam);
		army.addUnit(u, 5);
		expect(army.getAmountOfUniqueUnits() == 9);
		};
}
void Army::addUnitTest() {
	std::string namesol("Solider 1");
	unitHelpers::Cycling soliderCycle(10, 2, true);
	std::map<unitHelpers::unitTypes, double> soliderPowerCoef = { {unitHelpers::aviation,0.05}, {unitHelpers::infantry,1},
	{unitHelpers::armoredVehickle,0.15}, {unitHelpers::artilery,0.1} };
	Item item(soliderPowerCoef, "Item name", 313, 31);
	MoralUnitBuilder build;
	build.setCycling(soliderCycle)->setFortificationTarget(false)->setName(namesol)->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
		->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::infantry)->addItem(item)->addItem(item)->setMorality(75.4, 1);
	MoralUnit solider = *std::dynamic_pointer_cast<MoralUnit>(build.getResult());
	build.reset();
	build.setCycling(soliderCycle)->setFortificationTarget(false)->setName("solider 2")->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
		->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::armoredVehickle)->addItem(item);
	Unit solider2 = *build.getResult();
	build.reset();
	build.setCycling(soliderCycle)->setFortificationTarget(true)->setName("solider 3")->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
		->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::armoredVehickle);
	Unit solider3 = *build.getResult();
	build.reset();
	//******************************
	std::string nameavi("F-16");
	unitHelpers::Cycling aviCycle(8, 2, true);
	std::map<unitHelpers::unitTypes, double> aviPowerCoef = { {unitHelpers::aviation,1}, {unitHelpers::infantry,0.2},
	{unitHelpers::armoredVehickle,0.8}, {unitHelpers::artilery,0.8} };
	build.setCycling(aviCycle)->setFortificationTarget(false)->setName(nameavi)->setPowerAndViability(200, 220, 600)->setPowerCoef(aviPowerCoef)
		->setTypes(unitHelpers::unitTypes::aviation, unitHelpers::unitTypes::aviation);
	Unit avi = *build.getResult();
	build.reset();
	//*****************************
	std::string nametank("T-64 Bulat");
	unitHelpers::Cycling tankCycle(12, 1, true);
	std::map<unitHelpers::unitTypes, double> tankPowerCoef = { {unitHelpers::aviation,0.01}, {unitHelpers::infantry,1.3},
	{unitHelpers::armoredVehickle,1.5}, {unitHelpers::artilery,0.5} };
	build.setCycling(tankCycle)->setFortificationTarget(false)->setName(nametank)->setPowerAndViability(150, 200, 600)->setPowerCoef(tankPowerCoef)
		->setTypes(unitHelpers::unitTypes::armoredVehickle, unitHelpers::unitTypes::armoredVehickle);
	Unit tank = *build.getResult();
	build.reset();
	//*******************************
	std::string nameart("Caesar");
	unitHelpers::Cycling artCycle(10, 0, true);
	std::map<unitHelpers::unitTypes, double> artPowerCoef = { {unitHelpers::aviation,0}, {unitHelpers::infantry,1.5},
	{unitHelpers::armoredVehickle,1}, {unitHelpers::artilery,0.8} };
	build.setCycling(artCycle)->setFortificationTarget(false)->setName(nameart)->setPowerAndViability(150, 150, 400)->setPowerCoef(artPowerCoef)
		->setTypes(unitHelpers::unitTypes::artilery, unitHelpers::unitTypes::armoredVehickle);
	Unit art = *build.getResult();
	build.reset();

	////*********************************************
	Army sortedArmy;
	sortedArmy.addUnit(solider, 4);
	sortedArmy.addUnit(solider2, 6);
	sortedArmy.addUnit(solider3, 3);
	sortedArmy.addUnit(avi, 5);
	sortedArmy.addUnit(tank, 3);
	Army temp = *this;
	*this = sortedArmy;
	using namespace boost::ut;
	"addUnit"_test = [&] {
		expect(units.size() == 3);
		addUnit(art, 2);
		expect(units.size() == 4);
		expect(positionOfFirstAlive[3] == 0);
		expect(units[3].size() == 2);
		Unit art1 = art;
		double dem = 10000;
		art1.takeDamage(dem);
		addUnit(art1, 4);
		expect(units[3].size() == 6);
		expect(positionOfFirstAlive[3] == 4);
		expect(unitTypesPositions[unitHelpers::artilery] == 3);
		expect(unitTypesPositions[unitHelpers::infantry] == 0);
		expect(unitTypesPositions[unitHelpers::armoredVehickle] == 2);
		expect(unitTypesPositions[unitHelpers::aviation] == 1);
		};
	*this = temp;
}

void ArmyTest::test() {
	sortTest();
	isUitsEqualTest();
	addUnitTest();
	getAmountOfUniqueUnitsTest();
}
Iterator* Army::createSequentiallyTypeIterator() {
	return new SequentiallyTypeIterator(units);
}
Iterator* Army::createEachTypeIterator() {
	return new EachTypeIterator(units);
}
EachTypeIterator::EachTypeIterator(const std::vector<std::vector<Unit*>>& units) :units(units) {
	curI = 0;
	curJ = 0;
}
bool EachTypeIterator::hasMore() {
	if (curI < units.size() && curJ < units[curI].size())
		return true;
	return false;
}
/// Return units in ascending order of raw number
Unit* EachTypeIterator::getNext() {
	if (hasMore()) {
		Unit* res = units[curI][curJ];
		++curI;
		int i = curI;
		if (curI >= units.size()) {
			curI = 0;
			curJ++;
		}
		while (units[curI].size() <= curJ) {
			++curI;
			if (curI == i)
				break;
			if (curI >= units.size()) {
				curI = 0;
				++curJ;
			}

		}
		return res;
	}
	return nullptr;
}
SequentiallyTypeIterator::SequentiallyTypeIterator(const std::vector<std::vector<Unit*>>& units) {
	this->units = units;
	curI = 0;
	curJ = 0;
}
bool SequentiallyTypeIterator::hasMore() {
	if (curI < units.size() && curJ < units[curI].size())
		return true;
	return false;
}
/// Return units in ascending order of column number
Unit* SequentiallyTypeIterator::getNext() {
	if (hasMore()) {
		Unit* res = units[curI][curJ];
		++curJ;
		if (units[curI].size() == curJ) {
			curJ = 0;
			++curI;
		}
		return res;
	}
	return nullptr;
}
MementoArmy::MementoArmy(const Army& army, int round) {
	for (int i = 0; i < army.units.size(); i++) {
		this->units.push_back(std::vector<Unit*>());
		for (int j = 0; j < army.units[i].size(); j++) {
			this->units[i].push_back(army.units[i][j]->clone());
		}
	}
	fortification = army.fortification->clone();
	supplies = army.supplies;
	this->round = round;
}
MementoArmy::~MementoArmy() {
	for (int i = 0; i < units.size(); i++) {
		for (int j = 0; j < units[i].size(); j++) {
			delete units[i][j];
		}
	}
	delete fortification;
}