#include "FileManager.h"
#include<iostream>
#include <cstdint>
#include <filesystem>
/// Write map in stream in binary format
void FileManager::writeMap(const std::map<unitHelpers::unitTypes, double>& map, std::fstream& stream) {
	int size = (int)map.size();
	stream.write((char*)&size, sizeof(int));
	for (auto& pair : map) {
		stream.write((char*)&pair.first, sizeof(pair.first));
		stream.write((char*)&pair.second, sizeof(pair.second));
	}
}
/// Read map from stream in binary format
std::map<unitHelpers::unitTypes, double> FileManager::readMap(std::fstream& stream) {
	std::map<unitHelpers::unitTypes, double> map;
	int size = 0;
	unitHelpers::unitTypes type = static_cast<unitHelpers::unitTypes>(0);
	double param = 0;
	stream.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		stream.read((char*)&type, sizeof(type));
		stream.read((char*)&param, sizeof(double));
		map[type] = param;
	}
	return map;
}
/// Write circumstance in stream in binary format
void FileManager::writeCircumstance(const Circumstance& circ, std::fstream& stream) {
	writeMap(circ.powerChanges, stream);
	stream.write((char*)&circ.name[0], sizeof(circ.name));
}
/// Read circumstance from stream in binary format
Circumstance FileManager::readCircumstance(std::fstream& stream) {
	std::map<unitHelpers::unitTypes, double> map;
	Circumstance circ(map, "default");
	circ.powerChanges = readMap(stream);
	stream.read((char*)&circ.name[0], sizeof(circ.name));
	return circ;
}
/// Write Item in stream in binary format
void FileManager::writeItem(const Item& item, std::fstream& stream) {
	writeMap(item.powerCoefChanges, stream);
	stream.write((char*)&item.name[0], sizeof(item.name));
	stream.write((char*)&item.changeViability, sizeof(double));
	stream.write((char*)&item.changeBasePower, sizeof(double));
	stream.write((char*)&item.isApplied, sizeof(bool));
}
/// Read Item from stream in binary format
Item FileManager::readItem(std::fstream& stream) {
	std::map<unitHelpers::unitTypes, double> map;
	Item item(map, "default",0,0);
	item.powerCoefChanges = readMap(stream);
	stream.read((char*)&item.name[0], sizeof(item.name));
	stream.read((char*)&item.changeViability, sizeof(double));
	stream.read((char*)&item.changeBasePower, sizeof(double));
	stream.read((char*)&item.isApplied, sizeof(bool));
	return item;
}
/// Write Unit in stream in binary format
void FileManager::writeBaseUnit(const Unit& unit, int amount, std::fstream& stream) {
	if (!stream.is_open())
		std::cerr << "File do not open!";
	stream.write((char*)&amount, sizeof(int));
	stream.write((char*)&unit.TYPE_ID, sizeof(int));
	stream.write((char*)&unit.minPower, sizeof(double));
	stream.write((char*)&unit.maxPower, sizeof(double));
	stream.write((char*)&unit.maxArmor, sizeof(double));
	stream.write((char*)&unit.currentArmor, sizeof(double));
	stream.write((char*)&unit.isRenovateArmor, sizeof(bool));
	stream.write((char*)&unit.viability, sizeof(double));
	stream.write((char*)&unit.alive, sizeof(bool));
	stream.write((char*)&unit.fortificationTarget, sizeof(bool));
	stream.write((char*)&unit.name[0], sizeof(unit.name));
	stream.write((char*)&unit.cycling, sizeof(unit.cycling));
	stream.write((char*)&unit.type, sizeof(unit.type));
	stream.write((char*)&unit.priorityTarget, sizeof(unit.priorityTarget));
	writeMap(unit.powerCoef, stream);
	int size = (int)unit.items.size();
	stream.write((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		writeItem(unit.items[i], stream);
	}
}
/// Read Unit from stream in binary format
Unit* FileManager::readBaseUnit(std::fstream& stream) {
	std::map<unitHelpers::unitTypes, double> map;
	Unit* unit = new Unit();
	stream.read((char*)&unit->minPower, sizeof(double));
	stream.read((char*)&unit->maxPower, sizeof(double));
	stream.read((char*)&unit->maxArmor, sizeof(double));
	stream.read((char*)&unit->currentArmor, sizeof(double));
	stream.read((char*)&unit->isRenovateArmor, sizeof(bool));
	stream.read((char*)&unit->viability, sizeof(double));
	stream.read((char*)&unit->alive, sizeof(bool));
	stream.read((char*)&unit->fortificationTarget, sizeof(bool));
	stream.read((char*)&unit->name[0], sizeof(unit->name));
	stream.read((char*)&unit->cycling, sizeof(unit->cycling));
	stream.read((char*)&unit->type, sizeof(unit->type));
	stream.read((char*)&unit->priorityTarget, sizeof(unit->priorityTarget));
	unit->powerCoef = readMap(stream);
	int size=0;
	stream.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		unit->items.push_back(readItem(stream));
	}
	return unit;
}
/// Write MoralUnit in stream in binary format
void FileManager::writeMoralUnit(const MoralUnit& unit, int amount, std::fstream& stream) {
	if (!stream.is_open())
		std::cerr << "File do not open!";
	stream.write((char*)&amount, sizeof(int));
	stream.write((char*)&unit.TYPE_ID, sizeof(int));
	stream.write((char*)&unit.morality, sizeof(double));
	stream.write((char*)&unit.rateOfMoralityChanges, sizeof(double));
	stream.write((char*)&unit.minPower, sizeof(double));
	stream.write((char*)&unit.maxPower, sizeof(double));
	stream.write((char*)&unit.maxArmor, sizeof(double));
	stream.write((char*)&unit.currentArmor, sizeof(double));
	stream.write((char*)&unit.isRenovateArmor, sizeof(bool));
	stream.write((char*)&unit.viability, sizeof(double));
	stream.write((char*)&unit.alive, sizeof(bool));
	stream.write((char*)&unit.fortificationTarget, sizeof(bool));
	stream.write((char*)&unit.name[0], sizeof(unit.name));
	stream.write((char*)&unit.cycling, sizeof(unit.cycling));
	stream.write((char*)&unit.type, sizeof(unit.type));
	stream.write((char*)&unit.priorityTarget, sizeof(unit.priorityTarget));
	writeMap(unit.powerCoef, stream);
	int size = (int)unit.items.size();
	stream.write((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		writeItem(unit.items[i], stream);
	}
}
/// Read MoralUnit from stream in binary format
MoralUnit* FileManager::readMoralUnit(std::fstream& stream) {
	std::map<unitHelpers::unitTypes, double> map;
	MoralUnit* unit = new MoralUnit();
	stream.read((char*)&unit->morality, sizeof(double));
	stream.read((char*)&unit->rateOfMoralityChanges, sizeof(double));
	stream.read((char*)&unit->minPower, sizeof(double));
	stream.read((char*)&unit->maxPower, sizeof(double));
	stream.read((char*)&unit->maxArmor, sizeof(double));
	stream.read((char*)&unit->currentArmor, sizeof(double));
	stream.read((char*)&unit->isRenovateArmor, sizeof(bool));
	stream.read((char*)&unit->viability, sizeof(double));
	stream.read((char*)&unit->alive, sizeof(bool));
	stream.read((char*)&unit->fortificationTarget, sizeof(bool));
	stream.read((char*)&unit->name[0], sizeof(unit->name));
	stream.read((char*)&unit->cycling, sizeof(unit->cycling));
	stream.read((char*)&unit->type, sizeof(unit->type));
	stream.read((char*)&unit->priorityTarget, sizeof(unit->priorityTarget));
	unit->powerCoef = readMap(stream);
	int size = 0;
	stream.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		unit->items.push_back(readItem(stream));
	}
	return unit;
}
/// Read Unit from stream in binary format, depends on type
/*!
* \param[out] amount how much units writed in file
* \param[in,out] stream stream, for reading from file
*/
Unit* FileManager::readUnit(std::fstream& stream, int& amount) {
	if (!stream.is_open())
		std::cerr << "File do not open!";
	int type = 0;
	stream.read((char*)&amount, sizeof(int));
	stream.read((char*)&type, sizeof(int));
	switch (type) ///< Read unit depends on type
	{
	case 0:
		return  readBaseUnit(stream); ///< Base Unit
		break;
	case 1:
		return  readMoralUnit(stream); ///< MoralUnit
		break;
	}
	return new Unit();
}
/// Write Unit from stream in binary format, depends on type
/*!
* \param[in] amount how much units write to file. If < 1, return.
* \param[in,out] stream stream, for reading from file
* \param[in] unit unit, to write in file
*/
void FileManager::writeUnit(Unit* unit, int amount, std::fstream& stream) {
	if (amount < 1)
		return;
	switch (unit->getTypeID())
	{
	case 0:
		return  writeBaseUnit(*unit, amount, stream);
		break;
	case 1:
		return  writeMoralUnit(*((MoralUnit*)unit), amount, stream);
		break;
	}
}
/// Write Army in file in binary format
void FileManager::writeArmy(Army& army, const std::string& fileName) {
	std::fstream stream;
	stream.open(fileName, std::ios::binary | std::ios::out |std::ios::app);
	if (!stream.is_open())
		std::cerr << "File do not open!";
	army.sort(); ///< sorting army
	army.countViability();
	stream.write((char*)&army.name[0], sizeof(army.name));
	stream.write((char*)&army.viability, sizeof(double));
	stream.write((char*)&army.supplies, sizeof(double));
	writeMap(army.power, stream);
	writeUnit(army.fortification, 1, stream);
	int size = 0; ///< Find amount of unique units in army
	for (int i = 0; i < army.units.size(); i++) {
		for (int j = 0; j < army.units[i].size(); j++) {
			while (j + 1 < (int)army.units[i].size() && army.units[i][j]->isEqual(army.units[i][j+1])) {
				++j;
			}
			++size;
		}
	}
	stream.write((char*)&size, sizeof(int));///< Write amount of unique units in army
	for (int i = 0; i < army.units.size(); i++) {
		int amount = 1;
		for (int j = 0; j < (int)army.units[i].size(); j++) {
			int k = j;
			while (k + 1 < (int)army.units[i].size() && army.units[i][k]->isEqual(army.units[i][k + 1])) {
				amount++;
				k++;
				j++;
			}
			writeUnit(army.units[i][j], amount, stream); ///< Write unique units with theirs amount
			amount = 1;
		}
	}
	stream.close();
}
/// Read Army from file in binary format
Army FileManager::readArmy(const std::string& fileName) {
	Army army;
	std::fstream stream;
	stream.open(fileName, std::ios::binary | std::ios::in );
	if (!stream.is_open())
		std::cerr << "File do not open!";
	stream.read((char*)&army.name[0], sizeof(army.name));
	stream.read((char*)&army.viability, sizeof(double));
	stream.read((char*)&army.supplies, sizeof(double));
	army.power = readMap(stream);
	int amount = 1;
	army.fortification = readUnit(stream,amount);
	int size = 0;
	stream.read((char*)&size, sizeof(int));
	while (size>0)
	{
		Unit* u = readUnit(stream, amount);
		army.addUnit(*u, amount);
		--size;
		delete u;
	}
	stream.close();
	return army;
}
void FileManagerTest::itemTest() {
	using namespace boost::ut;
	std::string fileName = "itemTest";
	FileManager f;
	"item_read/write"_test = [&] {
		std::fstream s;
		s.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
		std::string namesol("Solider 1");
		unitHelpers::Cycling soliderCycle(10, 2, true);
		std::map<unitHelpers::unitTypes, double> soliderPowerCoef = { {unitHelpers::aviation,0.05}, {unitHelpers::infantry,1},
		{unitHelpers::armoredVehickle,0.15}, {unitHelpers::artilery,0.1} };
		Item item(soliderPowerCoef, "Item name", 313, 31);
		f.writeItem(item, s);
		expect(std::filesystem::exists(fileName) == true >> fatal);
		s.close();
		s.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
		Item item2 = f.readItem(s);
		expect(item.isEqual(item2) == true);
		s.close();
		expect(std::filesystem::remove(fileName) == true);
		};
}
void FileManagerTest::circumstanceTest() {
	using namespace boost::ut;
	std::string fileName = "circumstanceTest";
	FileManager f;
	"circumstance_read/write"_test = [&] {
		std::fstream s;
		s.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
		std::string namesol("Solider 1");
		unitHelpers::Cycling soliderCycle(10, 2, true);
		std::map<unitHelpers::unitTypes, double> soliderPowerCoef = { {unitHelpers::aviation,0.05}, {unitHelpers::infantry,1},
		{unitHelpers::armoredVehickle,0.15}, {unitHelpers::artilery,0.1} };
		Circumstance circ(soliderPowerCoef, "Circumstance name");
		f.writeCircumstance(circ, s);
		expect(std::filesystem::exists(fileName) == true >> fatal);
		s.close();
		s.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
		Circumstance circ2 = f.readCircumstance(s);
		expect(circ.isEqual(circ2) == true);
		s.close();
		expect(std::filesystem::remove(fileName) == true);
		};
}
void FileManagerTest::unitTest() {
	using namespace boost::ut;
	std::string fileName = "unitTest";
	FileManager f;
	"baseUnit_read/write"_test = [&] {
		std::fstream s;
		s.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
		std::string namesol("Solider 1");
		unitHelpers::Cycling soliderCycle(10, 2, true);
		std::map<unitHelpers::unitTypes, double> soliderPowerCoef = { {unitHelpers::aviation,0.05}, {unitHelpers::infantry,1},
		{unitHelpers::armoredVehickle,0.15}, {unitHelpers::artilery,0.1} };
		Item item(soliderPowerCoef, "Item name", 313, 31);
		UnitBuilder builder;
		Unit unit1 = builder.setCycling(soliderCycle)->setFortificationTarget(false)->setName(namesol)->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
			->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::infantry)->addItem(item)->addItem(item)->setArmor(30,true)->getResult();
		f.writeUnit(&unit1, 3 ,s);
		expect(std::filesystem::exists(fileName) == true >> fatal);
		s.close();
		s.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
		int amount = 0;
		Unit* unit2 = f.readUnit(s,amount);
		expect(unit1.isEqual(unit2) == true);
		expect(amount == 3);
		delete unit2;
		s.close();
		expect(std::filesystem::remove(fileName) == true);
		};
	"MoralUnit_read/write"_test = [&] {
		std::fstream s;
		s.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
		std::string namesol("Solider 1");
		unitHelpers::Cycling soliderCycle(10, 2, true);
		std::map<unitHelpers::unitTypes, double> soliderPowerCoef = { {unitHelpers::aviation,0.05}, {unitHelpers::infantry,1},
		{unitHelpers::armoredVehickle,0.15}, {unitHelpers::artilery,0.1} };
		Item item(soliderPowerCoef, "Item name", 313, 31);
		MoralUnitBuilder builder;
		MoralUnit unit1 = builder.setCycling(soliderCycle)->setMorality(72.2,2)->setFortificationTarget(false)->setName(namesol)->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
			->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::infantry)->addItem(item)->addItem(item)->setArmor(30, true)->getResult();
		f.writeUnit(&unit1, 3, s);
		expect(std::filesystem::exists(fileName) == true >> fatal);
		s.close();
		s.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
		int amount = 0;
		Unit* unit2 = f.readUnit(s, amount);
		expect(unit1.isEqual(unit2) == true);
		expect(amount == 3);
		delete unit2;
		s.close();
		expect(std::filesystem::remove(fileName) == true);
		};
}

void FileManagerTest::armyTest() {
	std::string namesol("Solider 1");
	unitHelpers::Cycling soliderCycle(10, 2, true);
	std::map<unitHelpers::unitTypes, double> soliderPowerCoef = { {unitHelpers::aviation,0.05}, {unitHelpers::infantry,1},
	{unitHelpers::armoredVehickle,0.15}, {unitHelpers::artilery,0.1}};
	Item item(soliderPowerCoef, "Item name", 313, 31);
	MoralUnitBuilder build;
	build.setCycling(soliderCycle)->setFortificationTarget(false)->setName(namesol)->setPowerAndViability(25,50, 100)->setPowerCoef(soliderPowerCoef)
		->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::infantry)->addItem(item)->addItem(item)->setMorality(75.4,1);
	MoralUnit solider = build.getResult();
	build.reset();
	build.setCycling(soliderCycle)->setFortificationTarget(false)->setName("solider 2")->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
		->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::armoredVehickle)->addItem(item);
	Unit solider2 = build.getResult();
	build.reset();
	build.setCycling(soliderCycle)->setFortificationTarget(true)->setName("solider 3")->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
		->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::armoredVehickle);
	Unit solider3 = build.getResult();
	build.reset();
	//******************************
	std::string nameavi("F-16");
	unitHelpers::Cycling aviCycle(8, 2, true);
	std::map<unitHelpers::unitTypes, double> aviPowerCoef = { {unitHelpers::aviation,1}, {unitHelpers::infantry,0.2},
	{unitHelpers::armoredVehickle,0.8}, {unitHelpers::artilery,0.8} };
	build.setCycling(aviCycle)->setFortificationTarget(false)->setName(nameavi)->setPowerAndViability(200,220, 600)->setPowerCoef(aviPowerCoef)
		->setTypes(unitHelpers::unitTypes::aviation, unitHelpers::unitTypes::aviation);
	Unit avi = build.getResult();
	build.reset();
	//*****************************
	std::string nametank("T-64 Bulat");
	unitHelpers::Cycling tankCycle(12, 1, true);
	std::map<unitHelpers::unitTypes, double> tankPowerCoef = { {unitHelpers::aviation,0.01}, {unitHelpers::infantry,1.3},
	{unitHelpers::armoredVehickle,1.5}, {unitHelpers::artilery,0.5} };
	build.setCycling(tankCycle)->setFortificationTarget(false)->setName(nametank)->setPowerAndViability(150,200, 600)->setPowerCoef(tankPowerCoef)
		->setTypes(unitHelpers::unitTypes::armoredVehickle, unitHelpers::unitTypes::armoredVehickle);
	Unit tank = build.getResult();
	build.reset();
	//*******************************
	std::string nameart("Caesar");
	std::string namepatr("Patriot");
	unitHelpers::Cycling artCycle(10, 0, true);
	std::map<unitHelpers::unitTypes, double> artPowerCoef = { {unitHelpers::aviation,0}, {unitHelpers::infantry,1.5},
	{unitHelpers::armoredVehickle,1}, {unitHelpers::artilery,0.8} };
	std::map<unitHelpers::unitTypes, double> patrPowerCoef = { {unitHelpers::aviation,2}, {unitHelpers::infantry,0.2},
	{unitHelpers::armoredVehickle,0.3}, {unitHelpers::artilery,0.3} };
	build.setCycling(artCycle)->setFortificationTarget(false)->setName(nameart)->setPowerAndViability(150,150, 400)->setPowerCoef(artPowerCoef)
		->setTypes(unitHelpers::unitTypes::artilery, unitHelpers::unitTypes::armoredVehickle);
	Unit art = build.getResult();
	build.reset();
	build.setCycling(artCycle)->setFortificationTarget(false)->setName(namepatr)->setPowerAndViability(150,150, 450)->setPowerCoef(patrPowerCoef)
		->setTypes(unitHelpers::unitTypes::artilery, unitHelpers::unitTypes::aviation)->setArmor(12,true);
	Unit patr = build.getResult();
	build.reset();
	////*********************************************
	Army army1;
	army1.setName("Army for testing");
	army1.changeSupplies(23232);
	army1.addUnit(solider, 4);
	army1.addUnit(solider2, 7);
	army1.addUnit(solider3, 3);
	army1.addUnit(avi, 5);
	army1.addUnit(tank, 3);
	army1.addUnit(art, 4);	
	army1.addUnit(patr, 3);
	using namespace boost::ut;
	std::string fileName = "armyTest";
	FileManager f;
	"MoralUnit_read/write"_test = [&] {
		army1.countPower();
		army1.countViability();
		f.writeArmy(army1,fileName);
		expect(std::filesystem::exists(fileName) == true >> fatal);
		Army army2 = f.readArmy(fileName);
		expect(army1.isUnitsEqual(army2) == true);
		expect(isMapsEqual(army1.getPower(),army2.getPower()));
		expect(army1.getViability() == army2.getViability());
		expect(army1.getSupplies() == army2.getSupplies());
		expect(army1.getName() == army2.getName());
		expect(std::filesystem::remove(fileName) == true);
		};
}
void FileManagerTest::test() {
	itemTest();
	circumstanceTest();
	unitTest();
	armyTest();
}
/// Is two maps equal
bool FileManagerTest::isMapsEqual(std::map<unitHelpers::unitTypes, double> map1, std::map<unitHelpers::unitTypes, double> map2) const {
	bool res = true;
	for (auto& pair : map1) {
		res = map1.at(pair.first) == map2.at(pair.first);
		if (!res)
			return false;
	}
	for (auto& pair : map2) {
		try {
			res = map1.at(pair.first) == map2.at(pair.first);
			if (!res)
				return false;
		}
		catch (const std::out_of_range&) {
			return false;
		}
	}
	return true;
}