#pragma once
#include"MoralUnit.h"
#include<fstream>
#include"Army.h"
/// Class for write/read objects in/from binary files
class FileManager
{
	void writeMap(const std::map<unitHelpers::unitTypes, double>& map, std::fstream& stream);
	std::map<unitHelpers::unitTypes, double> readMap(std::fstream& stream);
	void writeBaseUnit(const Unit& unit, int amount, std::fstream& stream);
	Unit* readBaseUnit(std::fstream& stream);
	void writeMoralUnit(const MoralUnit& unit, int amount, std::fstream& stream);
	MoralUnit* readMoralUnit(std::fstream& stream);
public:
	void writeItem(const Item& item, std::fstream& stream);
	Item readItem(std::fstream& stream);
	void writeUnit(Unit* unit, int amount, std::fstream& stream);
	Unit* readUnit(std::fstream& stream, int& amount);
	void writeArmy(Army& army, const std::string& fileName);
	Army readArmy(const std::string& fileName);
	void writeCircumstance(const Circumstance& circ, std::fstream& stream);
	Circumstance readCircumstance(std::fstream& stream);
};

class FileManagerTest {
	bool isMapsEqual(std::map<unitHelpers::unitTypes, double> map1, std::map<unitHelpers::unitTypes, double> map2) const;
	void itemTest();
	void unitTest();
	void circumstanceTest();
	void armyTest();
public:
	void test();
};