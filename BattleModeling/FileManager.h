#pragma once
#include"MoralUnit.h"
#include<fstream>
class FileManager
{
	void writeMap(const std::map<unitHelpers::unitTypes, double>& map, std::fstream& stream);
	std::map<unitHelpers::unitTypes, double> readMap(std::fstream& stream);
public:
	void writeItem(const Item& item, const std::string& fileName);
	Item readItem(std::fstream& stream);
	void writeBaseUnit(const Unit& unit, int amount, const std::string& fileName);
	Unit& readBaseUnit(const std::string& fileName, int& amount);
	void writeMoralUnit(const MoralUnit& unit, int amount, const std::string& fileName);
	MoralUnit& readMoralUnit(const std::string& fileName, int& amount);
	Unit& readUnit(const std::string& fileName, int& amount);
};

