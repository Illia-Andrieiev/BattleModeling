#include<iostream>
#include"BattleModeling.h"
#include"MoralUnit.h"
#include<omp.h>

using namespace std;
void pr(int num) {
	for (int i = 0; i < 100; i++) {
		cout << num << endl;
	}
}
void sum(const vector<int>& arr, int start, int end)
{
	int result = 0;
	for (int i = start; i < end; ++i)
	{
		cout << i<<" ";
	}
}
class A {
public:
	virtual void pr() {
		cout << "CLass A" << endl;
	}
	void pr1() {
		pr();
	}
};
class B :public A {
	int b = 13;
	void pr() override {
		cout << "CLass B " << b << endl;
	}
};

int main() {
	//UnitBuilder build;
	//Army army1;
	//Army army2;
	//army1.changeSupplies(9999999);
	//army2.changeSupplies(9999999);
	////******************************
	//string namesol("Snake");
	//unitHelpers::Cycling soliderCycle(10, 2, true);
	//std::map<unitHelpers::unitTypes, double> soliderPowerCoef = { {unitHelpers::aviation,0.05}, {unitHelpers::infantry,1},
	//{unitHelpers::armoredVehickle,0.15}, {unitHelpers::artilery,0.1}};
	//build.setCycling(soliderCycle)->setFortificationTarget(false)->setName(namesol)->setPowerAndViability(50, 100)->setPowerCoef(soliderPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::infantry, unitHelpers::unitTypes::infantry);
	//Unit solider = build.getResult();
	//build.reset();
	////******************************
	//string nameavi("F-16");
	//unitHelpers::Cycling aviCycle(8, 2, true);
	//std::map<unitHelpers::unitTypes, double> aviPowerCoef = { {unitHelpers::aviation,1}, {unitHelpers::infantry,0.2},
	//{unitHelpers::armoredVehickle,0.8}, {unitHelpers::artilery,0.8} };
	//build.setCycling(aviCycle)->setFortificationTarget(false)->setName(nameavi)->setPowerAndViability(200, 600)->setPowerCoef(aviPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::aviation, unitHelpers::unitTypes::aviation);
	//Unit avi = build.getResult();
	//build.reset();
	////*****************************
	//string nametank("T-64 Bulat");
	//unitHelpers::Cycling tankCycle(12, 1, true);
	//std::map<unitHelpers::unitTypes, double> tankPowerCoef = { {unitHelpers::aviation,0.01}, {unitHelpers::infantry,1.3},
	//{unitHelpers::armoredVehickle,1.5}, {unitHelpers::artilery,0.5} };
	//build.setCycling(tankCycle)->setFortificationTarget(false)->setName(nametank)->setPowerAndViability(200, 600)->setPowerCoef(tankPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::armoredVehickle, unitHelpers::unitTypes::armoredVehickle);
	//Unit tank = build.getResult();
	//build.reset();
	////*******************************
	//string nameart("Caesar");
	//string namepatr("Patriot");
	//unitHelpers::Cycling artCycle(10, 0, true);
	//std::map<unitHelpers::unitTypes, double> artPowerCoef = { {unitHelpers::aviation,0}, {unitHelpers::infantry,1.5},
	//{unitHelpers::armoredVehickle,1}, {unitHelpers::artilery,0.8} };
	//std::map<unitHelpers::unitTypes, double> patrPowerCoef = { {unitHelpers::aviation,2}, {unitHelpers::infantry,0.2},
	//{unitHelpers::armoredVehickle,0.3}, {unitHelpers::artilery,0.3} };
	//build.setCycling(artCycle)->setFortificationTarget(false)->setName(nameart)->setPowerAndViability(150, 400)->setPowerCoef(artPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::artilery, unitHelpers::unitTypes::armoredVehickle);
	//Unit art = build.getResult();
	//build.reset();
	//build.setCycling(artCycle)->setFortificationTarget(false)->setName(namepatr)->setPowerAndViability(150, 450)->setPowerCoef(patrPowerCoef)
	//	->setTypes(unitHelpers::unitTypes::artilery, unitHelpers::unitTypes::aviation);
	//Unit patr = build.getResult();
	//build.reset();
	////*********************************************
	//army1.addUnit(solider, 120);
	//army2.addUnit(solider, 60);
	//army1.addUnit(avi, 10);
	//army2.addUnit(avi, 6);
	//army1.addUnit(tank, 15);
	//army2.addUnit(tank, 9);
	//army1.addUnit(art, 11);	
	//army2.addUnit(art, 12);
	//army1.addUnit(patr, 5);
	//army2.addUnit(patr,6);
	//BattleBuilder builder;
	//BattleModeling battle = builder.setArmy(army1, army2)->getResult();
	//cout << army1.countViability() << "  " << army2.countViability();
	//battle();
	Unit un;
	MoralUnit morun;
	cout << "Unit type_id: " << un.TYPE_ID<<endl;
	cout << "MoralUnit type_id: " << morun.TYPE_ID << endl;
	return 0;
}