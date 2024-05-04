#include "Unit.h"
#include<random>
AttackArmy::AttackArmy(double damage, bool fortificationTarget) {
	this->damage = damage;
	this->fortificationTarget = fortificationTarget;
}
/// If fortificationTarget is true, 1/2 damage go to fortification. else all damage.
void AttackArmy::attackFortification(Unit& fortification, double& damage) {
	if (fortification.isAlive()) {
		if (!fortificationTarget) {
			double dam = damage / 2;
			fortification.takeDamage(dam);
			damage = damage / 2 + dam;
		}
		if (fortificationTarget)
			fortification.takeDamage(damage);
	}
}
/// Using uniform distribution choose randomly unit`s position. if cannot return -1 
int AttackArmy::chooseTargetNomer(std::vector<Unit*>& units, int firstAlive) {
	if (firstAlive == -1)
		return -1;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(firstAlive, (int)units.size() - 1);
	for (int i = 0; i < 120; i++) {
		int pos = distr(gen);
		if (units[pos]->getCycling().isActive)
			return pos;
	}
	return -1;
}
unitHelpers::Cycling Unit::getCycling() const {
	return cycling;
}
/// Attack fortification an foe`s units
void AttackArmy::attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<Unit*>& units) {
	attackFortification(fortification, damage);///< At first attack fortification 
	if (posFirstAlive == -1 || units.size() == 0)///< If all unnits dead, return;
		return;
	while (damage > 0 && posFirstAlive != -1) {///< While damage >0 and exists alive units in vector
		int pos = chooseTargetNomer(units, posFirstAlive); ///< Choose unit to attack
		if (pos == -1)///< If units do not choosed, return
			return;
		units[pos]->takeDamage(damage);///< attack unit
		if (!units[pos]->isAlive()) {
			std::swap(units[pos], units[posFirstAlive]);///< If unit dead, send him on vector`s start
			posFirstAlive++;///< Increase position of first alive
			if (posFirstAlive == units.size()) { ///< if position of first alive == vector`s size, set pos = -1
				posFirstAlive = -1;
			}
		}
	}
}
/// Choose type of unit to attack.
/*!
* Use uniform_real_distribution. Weight of types to attack defines as power*unit`sTypeCoef
*/
unitHelpers::unitTypes AttackArmy::chooseTarget(Army& army) const {
	return chooseRandomTarget(army);
}
/// Choose type of unit to attack.
/*!
* Use uniform_real_distribution. Weight of types to attack defines as power*unit`sTypeCoef
*/
unitHelpers::unitTypes AttackArmy::chooseRandomTarget(Army& army) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, (int)army.units.size() - 1);
	for (int i = 0; i < 100; i++) {
		int param = distr(gen);
		if (army.positionOfFirstAlive[army.unitTypesPositions[static_cast<unitHelpers::unitTypes>(param)]] != -1)
			return static_cast<unitHelpers::unitTypes>(param);
	}
	return static_cast<unitHelpers::unitTypes>(0);
}
/// Attack foes army if enough suoolies. Change supplies
/*!
* \param[in,out] army Army to attack
* \param[in,out] supplies Units supplies to attack army. Decrease supplies on 0.1*power.
*/
void AttackArmy::attackArmy(Army& army, double& supplies) {
	if (!prepareForAttack(supplies))
		return;
	double power = determinePower(); ///< Determine units power
	manageSupplies(supplies, power);
	unitHelpers::unitTypes type = chooseTarget(army);
	double damage = determineDamage(type, power); ///< find damage on type
	attackUnitType(*(army.fortification), damage, army.positionOfFirstAlive[army.unitTypesPositions[type]], army.units[army.unitTypesPositions[type]]);///< attack choosed type
}
/*



*/

void AttackArmyTest::attackFortificationTest() {
	using namespace boost::ut;
	Unit fortification;
	fortification.viability = 100;
	"attackFortification"_test = [&] {
		double damage = 50.0;
		bool fortificationTarget = false;

		AttackArmy attack(damage, fortificationTarget);
		attack.attackFortification(fortification, damage);

		expect(fortification.getViability());
		expect(damage);
		};
	fortification.viability = 100;
	"attackFortification (fortificationTarget is true)"_test = [&] {

		double damage = 50.0;
		bool fortificationTarget = true;

		AttackArmy attack(damage, fortificationTarget);
		attack.attackFortification(fortification, damage);

		expect(fortification.getViability() == 50);
		expect(damage == 0);
		};
	fortification.viability = 0;
	"attackFortification (fortification is dead)"_test = [&] {
		double damage = 50.0;
		bool fortificationTarget = false;

		AttackArmy attack(damage, fortificationTarget);
		attack.attackFortification(fortification, damage);

		expect(fortification.getViability() == 0);
		expect(damage);
		};
}
void AttackArmyTest::attackUnitTypeTest() {
	using namespace boost::ut;
	Unit fortification;
	fortification.viability = 100;
	Unit u1, u2;
	u1.viability = 50;
	u2.viability = 60;
	"attackUnitType (attack alive units)"_test = [&] {
		double damage = 50.0;
		int posFirstAlive = 0;
		std::vector<Unit*> units;
		units.push_back(&u1);
		units.push_back(&u2);

		AttackArmy attack(damage, false);
		attack.attackUnitType(fortification, damage, posFirstAlive, units);

		expect(fortification.getViability() == 75 >> fatal);
		expect(units[0]->getViability() == 25 && units[1]->getViability() == 60 || units[1]->getViability() == 35 && units[0]->getViability() == 50 >> fatal);
		expect(posFirstAlive == 0 >> fatal);
		expect(damage == 0 >> fatal);
		};
	u1.viability = 20;
	u2.viability = 20;
	fortification.viability = 0;
	"attackUnitType (attack alive units)"_test = [&] {
		double damage = 30.0;
		int posFirstAlive = 0;
		std::vector<Unit*> units;
		units.push_back(&u1);
		units.push_back(&u2);

		AttackArmy attack(damage, false);
		attack.attackUnitType(fortification, damage, posFirstAlive, units);

		expect(fortification.getViability() == 0 >> fatal);
		expect(units[0]->getViability() == 0 && units[1]->getViability() == 10 || units[0]->getViability() == 10 && units[1]->getViability() == 0 >> fatal);
		expect(posFirstAlive == 1 >> fatal);
		expect(damage == 0 >> fatal);
		};
}
void AttackArmyTest::test() {
	attackFortificationTest();
	attackUnitTypeTest();
}
/*



*/
/// Return is unit alive
bool Unit::isAlive() const {
	return alive;
}
/// Constructor
Unit::Unit() :AttackArmy(0, false) {
	type = static_cast<unitHelpers::unitTypes>(0);
	priorityTarget = static_cast<unitHelpers::unitTypes>(0);
	this->minPower = 0;
	this->maxPower = 0;
	std::string name = "default";
	for (int i = 0; i < name.size() && i < 256; i++)
		this->name[i] = name[i];
	this->viability = 0;
	this->alive = true;
	this->isRenovateArmor = false;
	this->maxArmor = 0;
	this->currentArmor = 0;
	fortificationTarget = false;
}
Unit& Unit::operator = (const Unit& unit) {
	if (this == &unit)
		return *this;
	this->cycling = unit.cycling;
	this->fortificationTarget = unit.fortificationTarget;
	for (int i = 0; i < 256; i++)
		this->name[i] = unit.name[i];
	this->minPower = unit.minPower;
	this->maxPower = unit.maxPower;
	this->viability = unit.viability;
	this->alive = unit.alive;
	this->powerCoef = unit.powerCoef;
	this->type = unit.type;
	this->isRenovateArmor = unit.isRenovateArmor;
	this->maxArmor = unit.maxArmor;
	this->currentArmor = unit.currentArmor;
	this->items = unit.items;
	this->priorityTarget = unit.priorityTarget;
	return *this;
}
///Get TYPE ID
int Unit::getTypeID() {
	return TYPE_ID;
}
/// Return is this unit equal to another
bool Unit::isEqual(Unit* unit) {
	if (this->TYPE_ID != unit->TYPE_ID || items.size() != unit->items.size())
		return false;
	bool res1 = true;
	for (int i = 0; i < items.size(); i++) {
		if (!res1)
			return false;
	}
	return this->alive == unit->alive && this->currentArmor == unit->currentArmor && this->cycling.isEqual(unit->cycling) &&
		this->fortificationTarget == unit->fortificationTarget && this->isRenovateArmor == unit->isRenovateArmor &&
		this->maxArmor == unit->maxArmor && this->maxPower == unit->maxPower && this->minPower == unit->minPower &&
		this->type == unit->type && this->viability == unit->viability && this->priorityTarget == unit->priorityTarget
		&& isMapsEqual(this->powerCoef, unit->powerCoef);
}
/// Decrease viability on damage points. If viability <= 0 set alive = false. 
/*!
*  Decrease damage on viability points. Set new morailty as old_morality * coef, where
*  coef = new_viabiliy/old_viability. 0.5 <= coef < 1. With 90% chanse armor takes damage
*/
void Unit::takeDamage(double& damage) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 9);
	if (distr(gen) != 9) {  ///< with 90% chanse armor take damage 
		this->currentArmor -= damage;
		if (currentArmor <= 0) {
			damage = -currentArmor;
			currentArmor = 0;
		}
		else
			damage = 0;
	}
	this->viability -= damage;///< Reduse viability
	if (viability <= 0) {
		alive = false;
		damage = -viability;
		viability = 0;
	}
	else
		damage = 0;
}
/// renovate armor value to maximum. Reduce supplies on 1 point for each 1 point of armor 
void Unit::renovateArmor(double& supplies) {
	if (isRenovateArmor) {
		if (currentArmor < maxArmor) {
			supplies -= (maxArmor - currentArmor);
			supplies = supplies < 0 ? 0 : supplies;
			currentArmor = maxArmor;
		}
	}
}
/// Return minimal unit`s power
double Unit::getMinBasePower() const {
	return minPower;
}
/// Return maximum unit`s power
double Unit::getMaxBasePower() const {
	return maxPower;
}
///Return unit`s name
std::string Unit::getName() const {
	return std::string(name);
}
/// Return unit`s viability
double Unit::getViability() const {
	return viability;
}
/// Return all unit`s items
std::vector<Item> Unit::getItems() const {
	return items;
}

std::string Unit::boolToStr(bool flag) {
	return flag ? "true" : "false";
}
/// Return string representation of MoralUnit
std::string Unit::toString() {
	std::string res("Name: " + std::string(name) + " viability: " + std::to_string(viability) + " alive: " + boolToStr(alive));
	for (int i = 0; i < items.size(); i++) {
		res = res + "; item " + std::to_string(i + 1) + ": " + items[i].toString();
	}
	return res;
}
///Multiply minPower and maxPower on koef
void Unit::multiplyPower(double koef) {
	if (koef < 0)
		return;
	this->minPower *= koef;
	this->maxPower *= koef;
}
/// Return is unit active now
bool Unit::getIsActive() const {
	return this->cycling.isActive;
}
///Return unit`s power koeficient
std::map<unitHelpers::unitTypes, double> Unit::getPowerCoef() const {
	return this->powerCoef;
}
/// Add 1 to current cycle. Manage isActive atribute
void Unit::updateCycle() {
	if (cycling.isActive) {
		cycling.currentCycle++;
		if (cycling.currentCycle >= cycling.cyclesToReplenishment) {
			cycling.currentCycle = 0;
			cycling.isActive = false;
		}
	}
	else {
		cycling.currentCycle++;
		if (cycling.currentCycle >= cycling.cyclesToActivation) {
			cycling.currentCycle = 0;
			cycling.isActive = true;
		}
	}
}

/// At first add all don`t applied items base parameters changes to unit. Then multiply item`s powerCoef on unit`s.
void Unit::applyItems() {
	for (int i = 0; i < items.size(); i++) {
		if (!items[i].isApply()) {
			minPower += items[i].getBasePowerChanges();
			maxPower += items[i].getBasePowerChanges();
			viability += items[i].getViabilityChanges();
		}
	}
	for (int i = 0; i < items.size(); i++) {
		if (!items[i].isApply()) {
			items[i].apply();
			for (auto& param : items[i].getPowerChanges()) {
				powerCoef[param.first] *= param.second;
			}
		}
	}
}
/// Using normal distribution determine power 
double  Unit::determinePower() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> distr(minPower, maxPower);
	return distr(gen);
}
bool Unit::prepareForAttack(const double& supplies) {
	if (!cycling.isActive) { ///< If unit unactive, update cycle and return
		updateCycle();
		return false;
	}
	updateCycle(); ///< update cycle
	if (supplies <= 0) ///< If not enough supplies, return
		return false;
	return true;
}
double Unit::determineDamage(unitHelpers::unitTypes type, double power) {
	double res = 1;
	try {
		res = power * powerCoef.at(type);
	}
	catch (const std::out_of_range&) {
		return power;
	}
	return res;
}
void Unit::manageSupplies(double& supplies, double power) {
	supplies -= power * 0.1; ///< change supplies
	supplies = supplies < 0 ? 0 : supplies;
	renovateArmor(supplies); ///< renovate armor
}
unitHelpers::unitTypes Unit::chooseTarget(Army& army) const {
	int posAlivePriorityTarget = army.positionOfFirstAlive[army.unitTypesPositions[priorityTarget]]; ///< find position of last alive priorityTarget unit 
	unitHelpers::unitTypes type = priorityTarget; ///< type to attack
	if (posAlivePriorityTarget == -1) ///< If all priority targets dead, choose type randomly
		type = chooseRandomTarget(army);
	return type;
}
/// Attack foes army if enough suoolies. Change supplies
/*!
* \param[in,out] army Army to attack
* \param[in,out] supplies Units supplies to attack army. Decrease supplies on 0.1*power.
*/
void Unit::attackArmy(Army& army, double& supplies) {

}
/// Return exact copy of this unit
Unit* Unit::clone() {
	Unit* newUnit = new Unit();
	newUnit->cycling = this->cycling;
	newUnit->fortificationTarget = this->fortificationTarget;
	for (int i = 0; i < 256; i++)
		newUnit->name[i] = this->name[i];
	newUnit->minPower = this->minPower;
	newUnit->maxPower = this->maxPower;
	newUnit->viability = this->viability;
	newUnit->powerCoef = this->powerCoef;
	newUnit->type = this->type;
	newUnit->alive = this->alive;
	newUnit->items = this->items;
	newUnit->priorityTarget = this->priorityTarget;
	newUnit->isRenovateArmor = this->isRenovateArmor;
	newUnit->maxArmor = this->maxArmor;
	newUnit->currentArmor = this->currentArmor;
	return newUnit;
}
/// Return default Unit, but with same type and priority target wis this
Unit* Unit::create() {
	Unit* res = new Unit();
	res->type = this->type;
	res->priorityTarget = this->priorityTarget;
	return res;
}
/// Is two maps equal
bool Unit::isMapsEqual(std::map<unitHelpers::unitTypes, double> map1, std::map<unitHelpers::unitTypes, double> map2) {
	bool res = true;
	for (auto& pair : map1) {
		res = map1.at(pair.first) == map2.at(pair.first);
		if (!res)
			return false;
	}
	for (auto& pair : map2) {
		res = map1.at(pair.first) == map2.at(pair.first);
		if (!res)
			return false;
	}
	return true;
}
/// Return unit`s type
unitHelpers::unitTypes Unit::getType() const {
	return type;

}
/// Return unit`s current armor
double Unit::getCurrentArmor() const {
	return currentArmor;
}
/*


*/
void UnitTest::isEqualTest() {
	using namespace boost::ut;
	"isEqual (all properties are equal)"_test = [&] {
		Unit u1 = builder.getResult();
		Unit u2 = builder.getResult();
		expect(u1.isEqual(&u2) == true >> fatal) << "Units must be equal!";
		};

	"isEqual (some properties are different)"_test = [&] {
		Unit u1 = builder.getResult();
		Unit u2 = builder.setArmor(50, false)->getResult();
		expect(u1.isEqual(&u2) == false);
		};
	builder.setArmor(0, false);
}
void UnitTest::applyItemsTest() {
	using namespace boost::ut;
	Unit u1 = builder.getResult();
	Unit u2 = builder.getResult();
	u1.items.clear();
	"applyItems_1"_test = [&] {
		double minPower = u1.getMinBasePower();
		double maxPower = u1.getMaxBasePower();
		double vi = u1.getViability();
		u1.applyItems();
		expect(minPower == u1.getMinBasePower() && maxPower == u1.getMaxBasePower());
		expect(vi == u1.getViability());
		};
	"applyItems_2"_test = [&] {
		u2.applyItems();
		expect(u2.getMinBasePower() == 87 && 112 == u2.getMaxBasePower() && 726 == u2.getViability());
		expect(u2.getPowerCoef()[unitHelpers::unitTypes::infantry] == 1);
		expect(u2.getPowerCoef()[unitHelpers::armoredVehickle] == 0.003375);
		};
	"applyItems_3"_test = [&] {
		u2.applyItems();
		expect(u2.getMinBasePower() == 87 && 112 == u2.getMaxBasePower());
		expect(726 == u2.getViability());
		expect(u2.getPowerCoef()[unitHelpers::unitTypes::infantry] == 1);
		expect(u2.getPowerCoef()[unitHelpers::armoredVehickle] == 0.003375);
		};
}
void UnitTest::takeDamageTest() {
	using namespace boost::ut;
	Unit u1 = builder.getResult();
	"takeDamage_1"_test = [&] {
		double dam = 40;
		u1.takeDamage(dam);
		expect(u1.getViability() == 60);
		expect(u1.isAlive());
		expect(dam == 0);
		};
	"takeDamage_2"_test = [&] {
		double dam = 100;
		u1.takeDamage(dam);
		expect(u1.getViability() == 0);
		expect(!u1.isAlive());
		expect(dam == 40);
		};
	u1 = builder.setArmor(50, false)->getResult();
	"takeDamage_3"_test = [&] {
		double dam = 80;
		u1.takeDamage(dam);
		expect(u1.getViability() == 20 && u1.getCurrentArmor() == 50 || u1.getViability() == 70 && u1.getCurrentArmor() == 0);
		expect(dam == 0);
		expect(u1.isAlive());
		};
}
void UnitTest::updateCycleTest() {
	using namespace boost::ut;

	"Unit::updateCycle (cycling is active)"_test = [] {
		Unit unit;
		unit.cycling.isActive = true;
		unit.cycling.currentCycle = 0;
		unit.cycling.cyclesToReplenishment = 3;
		unit.cycling.cyclesToActivation = 5;

		unit.updateCycle();

		expect(unit.cycling.isActive);
		expect(unit.cycling.currentCycle == 1);
		};

	"Unit::updateCycle (cycling is inactive)"_test = [] {
		Unit unit;
		unit.cycling.isActive = false;
		unit.cycling.currentCycle = 1;
		unit.cycling.cyclesToReplenishment = 3;
		unit.cycling.cyclesToActivation = 5;

		unit.updateCycle();

		expect(!unit.cycling.isActive);
		expect(unit.cycling.currentCycle == 2);
		};

	"Unit::updateCycle (cycling reaches cyclesToReplenishment)"_test = [] {
		Unit unit;
		unit.cycling.isActive = true;
		unit.cycling.currentCycle = 2;
		unit.cycling.cyclesToReplenishment = 3;
		unit.cycling.cyclesToActivation = 5;

		unit.updateCycle();

		expect(!unit.cycling.isActive);
		expect(unit.cycling.currentCycle == 0);
		};

	"Unit::updateCycle (cycling reaches cyclesToActivation)"_test = [] {
		Unit unit;
		unit.cycling.isActive = false;
		unit.cycling.currentCycle = 4;
		unit.cycling.cyclesToReplenishment = 3;
		unit.cycling.cyclesToActivation = 5;

		unit.updateCycle();

		expect(unit.cycling.isActive);
		expect(unit.cycling.currentCycle == 0);
		};
}
void UnitTest::cloneTest() {
	using namespace boost::ut;
	Unit u = builder.getResult();
	"clone_1"_test = [&] {
		Unit* u2 = u.clone();
		expect(u.isEqual(u2));
		delete u2;
		};
	"clone_2"_test = [&] {
		Unit* u2 = u.clone();
		u2->updateCycle();
		expect(!u.isEqual(u2));
		delete u2;
		};
}
void UnitTest::createTest() {
	using namespace boost::ut;
	Unit u = builder.getResult();
	"create_1"_test = [&] {
		Unit* u2 = u.create();
		expect(u.getType() == u2->getType());
		delete u2;
		};
}
UnitTest::UnitTest() {
	std::string namesol("Solider 1");
	unitHelpers::Cycling soliderCycle(10, 2, true);
	std::map<unitHelpers::unitTypes, double> soliderPowerCoef = { {unitHelpers::aviation,0.05}, {unitHelpers::infantry,1},
	{unitHelpers::armoredVehickle,0.15}, {unitHelpers::artilery,0.1} };
	Item item(soliderPowerCoef, "Item name", 313, 31);
	builder.setCycling(soliderCycle)->setFortificationTarget(false)->setName(namesol)->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
		->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::infantry)->addItem(item)->addItem(item);
}
void UnitTest::test() {
	isEqualTest();
	takeDamageTest();
	applyItemsTest();
	updateCycleTest();
	cloneTest();
	createTest();
}
/*


*/
/*
	Builder
*/
UnitBuilder::UnitBuilder() {
	reset();
}
UnitBuilder::UnitBuilder(Unit unit) {
	this->unit = unit;
}
void UnitBuilder::reset() {
	unit = Unit();
}
Unit UnitBuilder::getResult() {
	return unit;
}
UnitBuilder* UnitBuilder::setName(const std::string& name) {
	int i;
	for (i = 0; i < name.size() && i < 256; i++) {
		unit.name[i] = name[i];
	}
	for (; i < 256; i++) {
		unit.name[i] = '\0';
	}
	return this;
}
UnitBuilder* UnitBuilder::addItem(const Item& item) {
	unit.items.push_back(item);
	return this;
}
UnitBuilder* UnitBuilder::setPowerAndViability(double minPower, double maxPower, double viability) {
	if (minPower < 0 || maxPower <= 0 || viability <= 0)
		return this;
	unit.minPower = minPower;
	unit.maxPower = maxPower;
	unit.viability = viability;
	return this;
}
UnitBuilder* UnitBuilder::setFortificationTarget(bool fortificationTarget) {
	unit.fortificationTarget = fortificationTarget;
	return this;
}
UnitBuilder* UnitBuilder::setTypes(unitHelpers::unitTypes type, unitHelpers::unitTypes priorityTarget) {
	unit.type = type;
	unit.priorityTarget = priorityTarget;
	return this;
}
UnitBuilder* UnitBuilder::setPowerCoef(const std::map<unitHelpers::unitTypes, double>& powerCoef) {
	unit.powerCoef = powerCoef;
	return this;
}
UnitBuilder* UnitBuilder::setCycling(const unitHelpers::Cycling& cycling) {
	unit.cycling = cycling;
	return this;
}
UnitBuilder* UnitBuilder::setArmor(double armor, bool isRenovate) {
	if (armor < 0)
		armor = 0;
	unit.currentArmor = armor;
	unit.maxArmor = armor;
	unit.isRenovateArmor = isRenovate;
	return this;
}