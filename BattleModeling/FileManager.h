#pragma once
#include"MoralUnit.h"
#include<fstream>
#include"Army.h"
class FileManager
{
	void writeMap(const std::map<unitHelpers::unitTypes, double>& map, std::fstream& stream);
	std::map<unitHelpers::unitTypes, double> readMap(std::fstream& stream);
	void writeBaseUnit(const Unit& unit, int amount, std::fstream& stream);
	Unit readBaseUnit(std::fstream& stream);
	void writeMoralUnit(const MoralUnit& unit, int amount, std::fstream& stream);
	MoralUnit readMoralUnit(std::fstream& stream);
public:
	void writeItem(const Item& item, std::fstream& stream);
	Item readItem(std::fstream& stream);
	void writeUnit(Unit* unit, int amount, std::fstream& stream);
	Unit* readUnit(std::fstream& stream, int& amount);
	void writeArmy(Army& army, const std::string& fileName);
	Army readArmy(const std::string& fileName);
};

