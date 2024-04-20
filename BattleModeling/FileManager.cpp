#include "FileManager.h"
#include<iostream>
void FileManager::writeMap(const std::map<unitHelpers::unitTypes, double>& map, std::fstream& stream) {
	int size = (int)map.size();
	stream.write((char*)&size, sizeof(int));
	for (auto& pair : map) {
		stream.write((char*)&pair.first, sizeof(pair.first));
		stream.write((char*)&pair.second, sizeof(pair.second));
	}
}
std::map<unitHelpers::unitTypes, double> FileManager::readMap(std::fstream& stream) {
	std::map<unitHelpers::unitTypes, double> map;
	int size = 0;
	unitHelpers::unitTypes type = static_cast<unitHelpers::unitTypes>(0);
	double param=0; 
	stream.read((char*)&size, sizeof(int));
	for (int i = 0; i < size;i++) {
		stream.read((char*)&type, sizeof(type));
		stream.read((char*)&param, sizeof(double));
		map[type] = param;
	}
	return map;
}
void FileManager::writeItem(const Item& item, std::fstream& stream) {
	writeMap(item.powerCoefChanges, stream);
	stream.write((char*)&item.name[0], sizeof(item.name));
	stream.write((char*)&item.changeViability, sizeof(double));
	stream.write((char*)&item.changeBasePower, sizeof(double));
	stream.write((char*)&item.isApplied, sizeof(bool));
}
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
void FileManager::writeBaseUnit(const Unit& unit, int amount, const std::string& fileName) {
	std::fstream stream;
	stream.open(fileName, std::ios::binary | std::ios::out | std::ios::in|std::ios::app);
	if (!stream.is_open())
		std::cerr << "File do not open!";
	stream.write((char*)&amount, sizeof(int));
	stream.write((char*)&unit.TYPE_ID, sizeof(int));
	stream.write((char*)&unit.minPower, sizeof(double));
	stream.write((char*)&unit.maxPower, sizeof(double));
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
Unit FileManager::readBaseUnit(std::fstream& stream) {
	std::map<unitHelpers::unitTypes, double> map;
	Unit unit;
	stream.read((char*)&unit.minPower, sizeof(double));
	stream.read((char*)&unit.maxPower, sizeof(double));
	stream.read((char*)&unit.viability, sizeof(double));
	stream.read((char*)&unit.alive, sizeof(bool));
	stream.read((char*)&unit.fortificationTarget, sizeof(bool));
	stream.read((char*)&unit.name[0], sizeof(unit.name));
	stream.read((char*)&unit.cycling, sizeof(unit.cycling));
	stream.read((char*)&unit.type, sizeof(unit.type));
	stream.read((char*)&unit.priorityTarget, sizeof(unit.priorityTarget));
	unit.powerCoef = readMap(stream);
	int size=0;
	stream.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		unit.items.push_back(readItem(stream));
	}
	return unit;
}
void FileManager::writeMoralUnit(const MoralUnit& unit, int amount, const std::string& fileName) {
	std::fstream stream;
	stream.open(fileName, std::ios::binary | std::ios::out | std::ios::in | std::ios::app);
	if (!stream.is_open())
		std::cerr << "File do not open!";
	stream.write((char*)&amount, sizeof(int));
	stream.write((char*)&unit.TYPE_ID, sizeof(int));
	stream.write((char*)&unit.morality, sizeof(double));
	stream.write((char*)&unit.minPower, sizeof(double));
	stream.write((char*)&unit.maxPower, sizeof(double));
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
MoralUnit FileManager::readMoralUnit(std::fstream& stream) {
	std::map<unitHelpers::unitTypes, double> map;
	MoralUnit unit;
	stream.read((char*)&unit.morality, sizeof(double));
	stream.read((char*)&unit.minPower, sizeof(double));
	stream.read((char*)&unit.maxPower, sizeof(double));
	stream.read((char*)&unit.viability, sizeof(double));
	stream.read((char*)&unit.alive, sizeof(bool));
	stream.read((char*)&unit.fortificationTarget, sizeof(bool));
	stream.read((char*)&unit.name[0], sizeof(unit.name));
	stream.read((char*)&unit.cycling, sizeof(unit.cycling));
	stream.read((char*)&unit.type, sizeof(unit.type));
	stream.read((char*)&unit.priorityTarget, sizeof(unit.priorityTarget));
	unit.powerCoef = readMap(stream);
	int size = 0;
	stream.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		unit.items.push_back(readItem(stream));
	}
	return unit;
}
Unit* FileManager::readUnit(const std::string& fileName, int& amount) {
	std::fstream stream;
	stream.open(fileName, std::ios::binary | std::ios::out | std::ios::in);
	if (!stream.is_open())
		std::cerr << "File do not open!";
	int type = 0;
	stream.read((char*)&amount, sizeof(int));
	stream.read((char*)&type, sizeof(int));
	switch (type)
	{
	case 0:
		return  readBaseUnit(stream).clone();
		break;
	case 1:
		return  readMoralUnit(stream).clone();
		break;
	}
}
void FileManager::writeUnit(Unit* unit, int amount, const std::string& fileName) {
	switch (unit->getTypeID())
	{
	case 0:
		return  writeBaseUnit(*unit, amount, fileName);
		break;
	case 1:
		return  writeMoralUnit(*((MoralUnit*)unit), amount, fileName);
		break;
	}
}