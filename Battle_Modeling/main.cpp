#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include"BattleModeling.h"
#include"MoralUnit.h"
#include"FileManager.h"
#include<random>
//#include"libs/easy_plot_cpp-master/include/easy_plot.hpp"
using namespace std;
int main(int argc, char *argv[])
{

	//std::string namesol("Solider 1");
	//unitHelpers::Cycling soliderCycle(10, 2, true);
	//std::map<unitHelpers::unitTypes, double> soliderPowerCoef = { {unitHelpers::aviation,0.05}, {unitHelpers::infantry,1},
	//{unitHelpers::armoredVehickle,0.15}, {unitHelpers::artilery,0.1} };
	//Item item(soliderPowerCoef, "Item name", 313, 31);
	//MoralUnitBuilder build;
	//build.setCycling(soliderCycle)->setFortificationTarget(false)->setName(namesol)->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::infantry)->addItem(item)->addItem(item)->setMorality(75.4, 1);
	//MoralUnit solider = *std::dynamic_pointer_cast<MoralUnit>(build.getResult());
	//build.reset();
	//build.setCycling(soliderCycle)->setFortificationTarget(false)->setName("solider 2")->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::armoredVehickle)->addItem(item);
	//Unit solider2 = *build.getResult();
	//build.reset();
	//build.setCycling(soliderCycle)->setFortificationTarget(true)->setName("solider 3")->setPowerAndViability(25, 50, 100)->setPowerCoef(soliderPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::armoredVehickle);
	//Unit solider3 = *build.getResult();
	//build.reset();
	////******************************
	//std::string nameavi("F-16");
	//unitHelpers::Cycling aviCycle(8, 2, true);
	//std::map<unitHelpers::unitTypes, double> aviPowerCoef = { {unitHelpers::aviation,1}, {unitHelpers::infantry,0.2},
	//{unitHelpers::armoredVehickle,0.8}, {unitHelpers::artilery,0.8} };
	//build.setCycling(aviCycle)->setFortificationTarget(false)->setName(nameavi)->setPowerAndViability(200, 220, 600)->setPowerCoef(aviPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::aviation, unitHelpers::unitTypes::aviation);
	//Unit avi = *build.getResult();
	//build.reset();
	////*****************************
	//std::string nametank("T-64 Bulat");
	//unitHelpers::Cycling tankCycle(12, 1, true);
	//std::map<unitHelpers::unitTypes, double> tankPowerCoef = { {unitHelpers::aviation,0.01}, {unitHelpers::infantry,1.3},
	//{unitHelpers::armoredVehickle,1.5}, {unitHelpers::artilery,0.5} };
	//build.setCycling(tankCycle)->setFortificationTarget(false)->setName(nametank)->setPowerAndViability(150, 200, 600)->setPowerCoef(tankPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::armoredVehickle, unitHelpers::unitTypes::armoredVehickle);
	//Unit tank = *build.getResult();
	//build.reset();
	////*******************************
	//std::string nameart("Caesar");
	//std::string namepatr("Patriot");
	//unitHelpers::Cycling artCycle(10, 0, true);
	//std::map<unitHelpers::unitTypes, double> artPowerCoef = { {unitHelpers::aviation,0}, {unitHelpers::infantry,1.5},
	//{unitHelpers::armoredVehickle,1}, {unitHelpers::artilery,0.8} };
	//std::map<unitHelpers::unitTypes, double> patrPowerCoef = { {unitHelpers::aviation,2}, {unitHelpers::infantry,0.2},
	//{unitHelpers::armoredVehickle,0.3}, {unitHelpers::artilery,0.3} };
	//build.setCycling(artCycle)->setFortificationTarget(false)->setName(nameart)->setPowerAndViability(150, 150, 400)->setPowerCoef(artPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::artilery, unitHelpers::unitTypes::armoredVehickle);
	//Unit art = *build.getResult();
	//build.reset();
	//build.setCycling(artCycle)->setFortificationTarget(false)->setName(namepatr)->setPowerAndViability(150, 150, 450)->setPowerCoef(patrPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::artilery, unitHelpers::unitTypes::aviation)->setArmor(12, true);
	//Unit patr = *build.getResult();
	//build.reset();
	//////*********************************************
	//Army army1;
	//army1.setName("Army for testing");
	////army1.changeSupplies(23232);
	//army1.addUnit(solider, 4);
	//army1.addUnit(solider2, 7);
	//army1.addUnit(solider3, 3);
	//army1.addUnit(avi, 5);
	//army1.addUnit(tank, 3);
	//army1.addUnit(art, 4);
	//army1.addUnit(patr, 3);
	//Army army2;
	//army2.setName("Army for testing2");
	////army2.changeSupplies(23232);
	//army2.addUnit(solider, 4);
	//army2.addUnit(solider2, 7);
	//army2.addUnit(solider3, 3);
	////army2.addUnit(avi, 5);
	//army2.addUnit(tank, 3);
	//army2.addUnit(art, 4);
	//army2.addUnit(patr, 3);
	//BattleBuilder built;
	//Supply s;
	//s.army1RoundSupplies = 100;
	//s.army1StartSupplies = 99999;
	//s.army1SupplyRoundAmount = 100;
	//s.army2RoundSupplies = 100;
	//s.army2StartSupplies = 99999;
	//s.army2SupplyRoundAmount = 100;
	//BattleModeling battle = built.setArmy(army1,army2)->setSupplies(s)->getResult();
	//std::vector<std::pair<double, double>> points = battle();
	//ep::init(&argc, argv);
	//std::vector<double> first;
	//std::vector<double> second;
	//for (auto& pair : points) {
	//	first.push_back(pair.first);
	//	second.push_back(pair.second);
	//}
	//ep::WindowSpec wstyle;
	//ep::plot<double>("Army1 - red, Army2 - blue.",wstyle,2, first, ep::LineSpec(1, 0, 0), second, ep::LineSpec(0, 0, 1));
	//std::vector<double> x = { 0,1,0,1,2,0,1 };
	//ep::plot("X", x);

	//// ставим красный цвет линии
	//std::vector<double> y = { 0,2,3,4,2,0,1 };
	//ep::plot("Y", y, ep::LineSpec(1, 0, 0));
	//
	//std::vector<double> x2 = { 0,2,6,7,8,10,12 };
	//ep::plot("XY", x2, y, ep::LineSpec(1, 1, 0));

	//ep::WindowSpec wstyle; // тут можно настроить стиль графика (цвет фона и пр.)
	//// выводим три графика в одном
	//ep::plot<double>("Y1Y2Y3", wstyle, 3, x, ep::LineSpec(1, 0, 0), x2, ep::LineSpec(1, 0, 1), y, ep::LineSpec(0, 1, 0));
	//int ite = 0;
	//while (ite<10000000) {
	//	std::this_thread::yield();
	//	ite++;
	//}
	//return 0;
    QApplication a(argc, argv);
    MainWindow w(argc,argv);
    w.show();
    return a.exec();
}
