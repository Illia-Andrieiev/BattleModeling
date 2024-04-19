#include "FileManager.h"
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
	int size;
	unitHelpers::unitTypes type;
	double param; 
	stream.read((char*)&size, sizeof(int));
	for (int i = 0; i < size;i++) {
		stream.read((char*)&type, sizeof(type));
		stream.read((char*)&param, sizeof(double));
		map[type] = param;
	}
	return map;
}
void FileManager::writeItem(const Item& item, const std::string& fileName) {
	std::fstream stream;
	stream.open(fileName, std::ios::binary | std::ios::out | std::ios::in | std::ios::app);
	writeMap(item.powerCoefChanges, stream);
	stream.write((char*)&item.name[0], sizeof(item.name));
	stream.write((char*)&item.changeViability, sizeof(double));
	stream.write((char*)&item.changeBasePower, sizeof(double));
	stream.write((char*)&item.isApplied, sizeof(bool));
}
Item FileManager::readItem(std::fstream& stream) {
	std::map<unitHelpers::unitTypes, double> map;
	Item item(map, "name",0,0);
	item.powerCoefChanges = readMap(stream);
	stream.read((char*)&item.name[0], sizeof(item.name));
	stream.read((char*)&item.changeViability, sizeof(double));
	stream.read((char*)&item.changeBasePower, sizeof(double));
	stream.read((char*)&item.isApplied, sizeof(bool));
	return item;
}
void FileManager::writeBaseUnit(const Unit& unit, int amount, const std::string& fileName) {

}
Unit& FileManager::readBaseUnit(const std::string& fileName, int& amount) {
	MoralUnit u;
	return u;
}
void FileManager::writeMoralUnit(const MoralUnit& unit, int amount, const std::string& fileName) {

}
MoralUnit& FileManager::readMoralUnit(const std::string& fileName, int& amount) {
	MoralUnit u;
	return u;
}
Unit& FileManager::readUnit(const std::string& fileName, int& amount) {
	MoralUnit u;
	return u;
}