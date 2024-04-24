#include "FileManager.h"
#include<iostream>
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
* \param[in] amount how much units write to file
* \param[in,out] stream stream, for reading from file
* \param[in] unit unit, to write in file
*/
void FileManager::writeUnit(Unit* unit, int amount, std::fstream& stream) {
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