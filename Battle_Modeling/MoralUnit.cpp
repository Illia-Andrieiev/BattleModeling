#include "MoralUnit.h"
#include <random>
///Constructor
MoralUnit::MoralUnit() {
	this->morality = 100;
	this->rateOfMoralityChanges = 1;
}
/// Return units TYPE ID
int MoralUnit::getTypeID() {
	return TYPE_ID;
}
/// Return units morality
double MoralUnit::getMorality() const {
	return morality;
}
double MoralUnit::getMoralityChangesRate() const {
	return rateOfMoralityChanges;
}
MoralUnit& MoralUnit::operator = (const MoralUnit& unit) {
	if (this == &unit)
		return *this;
	this->cycling = unit.cycling;
	this->fortificationTarget = unit.fortificationTarget;
	for (int i = 0; i < 256; i++)
		this->name[i] = unit.name[i];
	this->minPower = unit.minPower;
	this->maxPower = unit.maxPower;
	this->alive = unit.alive;
	this->morality = unit.morality;
	this->viability = unit.viability;
	this->powerCoef = unit.powerCoef;
	this->type = unit.type;
	this->items = unit.items;
	this->alive = unit.alive;
	this->isRenovateArmor = unit.isRenovateArmor;
	this->maxArmor = unit.maxArmor;
	this->currentArmor = unit.currentArmor;
	this->priorityTarget = unit.priorityTarget;
	return *this;
}
/// Set morality
void MoralUnit::setMorality(double morality) {
	if (morality < 0)
		morality = 0;
	if (morality > 100)
		morality = 100;
	this->morality = morality;
}
/// Decrease viability on damage points. If viability <= 0 set alive = false. 
/*!
*  Decrease damage on viability points. Set new morailty as old_morality * coef, where
*  coef = new_viabiliy/old_viability. 0.5 <= coef < 1. With 90% chanse armor takes damage
*/
void MoralUnit::takeDamage(double& damage) {
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
	this->viability -= damage;
	if (viability <= 0) {
		alive = false;
		damage = -viability;
		viability = 0;
	}
	else { ///< If unit still alive, reduse morality 
		double coef = (this->viability / (this->viability + damage));
		coef < 0.5 ? coef = 0.5 : coef = coef;
		this->morality = this->morality * coef;
		damage = 0;
	}
}
/// Add 1 to current cycle. Manage isActive atribute. 
/*!
*   Increase morality by 2 each unactive round, decrease by 0.5 each active,
*   and increase by 3.5 at round, when unit go unactive.
*/
void MoralUnit::updateCycle() {
	if (cycling.isActive) {
		cycling.currentCycle++;
		if (cycling.currentCycle >= cycling.cyclesToReplenishment) {
			cycling.currentCycle = 0;
			cycling.isActive = false;
			setMorality(this->morality + 3.5);
			return;
		}
		setMorality(this->morality - 0.5 * rateOfMoralityChanges);
	}
	else {
		cycling.currentCycle++;
		if (cycling.currentCycle >= cycling.cyclesToActivation) {
			cycling.currentCycle = 0;
			cycling.isActive = true;
			return;
		}
		setMorality(this->morality + 2);
	}
}
/// Determine how much damage unit will cause on battle field. Use normal_distribution.
/*!
*   if morality >= 50 && morality < 85 : axPower = minPower + (maxPower - minPower) * morality / 100;
*   if morality < 50 : minPower *= (morality + 50) / 100, maxPower = minPower + (maxPower - minPower) * morality / 100;
*/
double MoralUnit::determinePower() {
	double minPower = this->minPower;
	double maxPower = this->maxPower;
	if (morality >= 50 && morality < 85) {
		maxPower = minPower + (maxPower - minPower) * morality / 100;
	}
	if (morality < 50) {
		double coef = (morality + 50) / 100;
		minPower *= coef;
		maxPower = minPower + (maxPower - minPower) * morality / 100;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(minPower, maxPower);
	return distr(gen);
}
/// Attack fortification an foe`s units
void MoralUnit::attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<Unit*>& units) {
	attackFortification(fortification, damage);///< At first attack fortification 
	if (posFirstAlive == -1 || units.size() == 0) ///< If all unnits dead, return;
		return;
	while (damage > 0 && posFirstAlive != -1) { ///< While damage >0 and exists alive units in vector
		int pos = chooseTargetNomer(units, posFirstAlive); ///< Choose unit to attack
		if (pos == -1) ///< If units do not choosed, return
			return;
		units[pos]->takeDamage(damage); ///< attack unit
		if (!units[pos]->isAlive()) {
			std::swap(units[pos], units[posFirstAlive]); ///< If unit dead, send him on vector`s start
			posFirstAlive++; ///< Increase position of first alive
			if (posFirstAlive == units.size()) { ///< if position of first alive == vector`s size, set pos = -1
				posFirstAlive = -1;
			}
			setMorality(this->morality + 5); ///< increase units morality
		}
	}
}
/// Return string representation of MoralUnit
std::string MoralUnit::toString() {
	return Unit::toString() + " morality: " + std::to_string(morality);
}
/// Return exact copy of this unit
MoralUnit* MoralUnit::clone() {
	MoralUnit* newUnit = new MoralUnit();
	newUnit->cycling = this->cycling;
	newUnit->fortificationTarget = this->fortificationTarget;
	for (int i = 0; i < 256; i++)
		newUnit->name[i] = this->name[i];
	newUnit->minPower = this->minPower;
	newUnit->maxPower = this->maxPower;
	newUnit->morality = this->morality;
	newUnit->rateOfMoralityChanges = this->rateOfMoralityChanges;
	newUnit->viability = this->viability;
	newUnit->powerCoef = this->powerCoef;
	newUnit->type = this->type;
	newUnit->items = this->items;
	newUnit->priorityTarget = this->priorityTarget;
	newUnit->isRenovateArmor = this->isRenovateArmor;
	newUnit->maxArmor = this->maxArmor;
	newUnit->currentArmor = this->currentArmor;
	return newUnit;
}
/// Return default MoralUnit, but with same type and priority target wis this
MoralUnit* MoralUnit::create() {
	MoralUnit* res = new MoralUnit();
	res->type = this->type;
	res->priorityTarget = this->priorityTarget;
	return res;
}
/// Is this unit equal to another
bool MoralUnit::isEqual(Unit* unit) {
	MoralUnit* unit1 = dynamic_cast<MoralUnit*>(unit);
	if (unit1 == nullptr || items.size() != unit1->items.size() || unit1->getTypeID() != TYPE_ID) {
		return false;
	}
	for (int i = 0; i < items.size(); i++) {
		if (!(items[i].isEqual(unit1->items[i])))
			return false;
	}
	return this->alive == unit1->alive && this->currentArmor == unit1->currentArmor && this->cycling.isEqual(unit1->cycling) &&
		this->morality == unit1->morality && this->rateOfMoralityChanges == unit1->rateOfMoralityChanges &&
		this->fortificationTarget == unit1->fortificationTarget && this->isRenovateArmor == unit1->isRenovateArmor &&
		this->maxArmor == unit1->maxArmor && this->maxPower == unit1->maxPower && this->minPower == unit1->minPower &&
		this->type == unit1->type && this->viability == unit1->viability && this->priorityTarget == unit1->priorityTarget
		&& isMapsEqual(this->powerCoef, unit1->powerCoef);
}
/*


*/
void MoralUnitTest::isEqualTest() {
	using namespace boost::ut;
	"isEqual (all properties are equal)"_test = [&] {
		MoralUnit u1 = *std::dynamic_pointer_cast<MoralUnit>(builder.getResult());
		MoralUnit u2 = *std::dynamic_pointer_cast<MoralUnit>(builder.getResult());
		expect(u1.isEqual(&u2) == true >> fatal) << "Units must be equal!";
		};

	"isEqual (some properties are different)"_test = [&] {
		MoralUnit u1 = *std::dynamic_pointer_cast<MoralUnit>(builder.getResult());
		MoralUnit u2 = *std::dynamic_pointer_cast<MoralUnit>(builder.setArmor(50, false)->getResult());
		expect(u1.isEqual(&u2) == false);
		};
	builder.setArmor(0, false);
}
void MoralUnitTest::attackUnitTypeTest() {
	using namespace boost::ut;
	MoralUnit fortification;
	fortification.viability = 100;
	MoralUnit u1, u2;
	u1.viability = 50;
	u2.viability = 60;
	MoralUnit un = *std::dynamic_pointer_cast<MoralUnit>(builder.getResult());
	"attackUnitType (attack alive units)"_test = [&] {
		double damage = 50.0;
		int posFirstAlive = 0;
		std::vector<Unit*> units;
		units.push_back(&u1);
		units.push_back(&u2);
		un.attackUnitType(fortification, damage, posFirstAlive, units);

		expect(fortification.getViability() == 75 >> fatal);
		expect(un.getMorality() == 90 && (units[0]->getViability() == 25 && units[1]->getViability() == 60 || units[1]->getViability() == 35 && units[0]->getViability() == 50) >> fatal);
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

		un.attackUnitType(fortification, damage, posFirstAlive, units);
		expect(fortification.getViability() == 0 >> fatal);
		expect(units[0]->getViability() == 0 && units[1]->getViability() == 10 || units[0]->getViability() == 10 && units[1]->getViability() == 0 >> fatal);
		expect(posFirstAlive == 1 >> fatal);
		expect(un.getMorality() == 95 >> fatal);
		expect(damage == 0 >> fatal);
		};
}
void MoralUnitTest::takeDamageTest() {
	using namespace boost::ut;
	MoralUnit u1 = *std::dynamic_pointer_cast<MoralUnit>(builder.getResult());
	"takeDamage_1"_test = [&] {
		double dam = 40;
		u1.takeDamage(dam);
		expect(u1.getViability() == 60 && dam == 0 && u1.isAlive() && u1.getMorality() == 54);
		};
	"takeDamage_2"_test = [&] {
		double dam = 100;
		u1.takeDamage(dam);
		expect(u1.getViability() == 0 && dam == 40 && !u1.isAlive());
		};
	u1 = *std::dynamic_pointer_cast<MoralUnit>(builder.setArmor(50, false)->getResult());
	"takeDamage_3"_test = [&] {
		double dam = 80;
		u1.takeDamage(dam);
		expect((u1.getViability() == 20 && u1.getCurrentArmor() == 50. && 49.98 <= u1.getMorality() && u1.getMorality() <= 50. || u1.getViability() == 70 && u1.getCurrentArmor() == 0 && 62.98 <= u1.getMorality() && u1.getMorality() <= 63.) && dam == 0 && u1.isAlive());
		};
}
void MoralUnitTest::cloneTest() {
	using namespace boost::ut;
	MoralUnit u = *std::dynamic_pointer_cast<MoralUnit>(builder.getResult());
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
void MoralUnitTest::createTest() {
	using namespace boost::ut;
	MoralUnit u = *std::dynamic_pointer_cast<MoralUnit>(builder.getResult());
	"create_1"_test = [&] {
		Unit* u2 = u.create();
		expect(u.getType() == u2->getType());
		delete u2;
		};
}
MoralUnitTest::MoralUnitTest() {
	std::string namesol("Solider 1");
	unitHelpers::Cycling soliderCycle(10, 2, true);
	std::map<unitHelpers::unitTypes, double> soliderPowerCoef = { {unitHelpers::aviation,0.05}, {unitHelpers::infantry,1},
	{unitHelpers::armoredVehickle,0.15}, {unitHelpers::artilery,0.1} };
	Item item(soliderPowerCoef, "Item name", 313, 31);
	builder.setCycling(soliderCycle)->setFortificationTarget(false)->setName(namesol)->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
		->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::infantry)->addItem(item)->addItem(item)->setMorality(90, 1);
}
void MoralUnitTest::test() {
	isEqualTest();
	takeDamageTest();
	cloneTest();
	createTest();
	attackUnitTypeTest();
}
/*


*/
/*
	Builder
*/
MoralUnitBuilder::MoralUnitBuilder() {
	reset();
}

void MoralUnitBuilder::reset() {
	unit = std::make_shared<MoralUnit>();
}
std::shared_ptr<Unit> MoralUnitBuilder::getResult() {
	return unit;
}
MoralUnitBuilder* MoralUnitBuilder::setName(const std::string& name) {
	int i;
	for (i = 0; i < name.size() && i < 256; i++) {
		unit->name[i] = name[i];
	}
	for (; i < 256; i++) {
		unit->name[i] = '\0';
	}
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::addItem(const Item& item) {
	unit->items.push_back(item);
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setPowerAndViability(double minPower, double maxPower, double viability) {
	if (minPower < 0 || maxPower <= 0 || viability <= 0)
		return this;
	unit->minPower = minPower;
	unit->maxPower = maxPower;
	unit->viability = viability;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setFortificationTarget(bool fortificationTarget) {
	unit->fortificationTarget = fortificationTarget;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setTypes(unitHelpers::unitTypes type, unitHelpers::unitTypes priorityTarget) {
	unit->type = type;
	unit->priorityTarget = priorityTarget;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setPowerCoef(const std::map<unitHelpers::unitTypes, double>& powerCoef) {
	unit->powerCoef = powerCoef;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setCycling(const unitHelpers::Cycling& cycling) {
	unit->cycling = cycling;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setMorality(double morality, double rateOfMoralityChanges = 1) {
	unit->setMorality(morality);
	if (rateOfMoralityChanges <= 0)
		rateOfMoralityChanges = 1;
	unit->rateOfMoralityChanges = rateOfMoralityChanges;
	return this;
}
MoralUnitBuilder* MoralUnitBuilder::setArmor(double armor, bool isRenovate) {
	if (armor < 0)
		armor = 0;
	unit->currentArmor = armor;
	unit->maxArmor = armor;
	unit->isRenovateArmor = isRenovate;
	return this;
}