#include<iostream>
#include"BattleModeling.h"


using namespace std;
int main() {
	ModernArmy army1;
	ModernArmy army2;
	army1.changeSupplies(9999999);
	army2.changeSupplies(9999999);
	string namesol("Snake");
	Cycling soliderCycle(10, 2, true);
	ModernPowerCoef soliderModernPowerCoef(0.05, 1, 0.15, 0.1);
	ModernUnit solider(namesol, 50, 100, false, soliderCycle, soliderModernPowerCoef);
	string nameavi("F-16");
	Cycling aviCycle(8, 2, true);
	ModernPowerCoef aviModernPowerCoef(1, 0.2, 0.8, 0.8);
	ModernUnit avi(nameavi, 300, 800, false, aviCycle, aviModernPowerCoef);
	string nametank("T-72");
	Cycling tankCycle(12, 1, true);
	ModernPowerCoef tankModernPowerCoef(0.01, 1.3, 1.5, 0.5);
	ModernUnit tank(nametank, 200, 600, false, tankCycle, tankModernPowerCoef);
	string nameart("Pion");
	string namepatr("Patriot");
	Cycling artCycle(10, 0, true);
	ModernPowerCoef artModernPowerCoef(0, 1.5, 1, 0.8);
	ModernPowerCoef patrModernPowerCoef(2, 0.2, 0.3, 0.3);
	ModernUnit art(nameart, 300, 400, false, artCycle, artModernPowerCoef);
	ModernUnit patr(namepatr, 300, 450, false, artCycle, patrModernPowerCoef);
	for (int i = 0; i < 50; i++) {
		army1.addUnit(solider, modernUnitTypes::infantry);
	}
	for (int i = 0; i < 65; i++) {
		army2.addUnit(solider, modernUnitTypes::infantry);
	}
	for (int i = 0; i < 8; i++) {
		army1.addUnit(avi, modernUnitTypes::aviation);
	}
	for (int i = 0; i < 6; i++) {
		army2.addUnit(avi, modernUnitTypes::aviation);
	}
	for (int i = 0; i < 10; i++) {
		army1.addUnit(tank, modernUnitTypes::armoredVehickle);
	}
	for (int i = 0; i < 15; i++) {
		army2.addUnit(tank, modernUnitTypes::armoredVehickle);
	}
	for (int i = 0; i < 25; i++) {
		army1.addUnit(art, modernUnitTypes::artilery);
	}
	for (int i = 0; i < 15; i++) {
		army2.addUnit(art, modernUnitTypes::artilery);
	}
	for (int i = 0; i < 10; i++) {
		army1.addUnit(patr, modernUnitTypes::artilery);
	}
	for (int i = 0; i < 8; i++) {
		army2.addUnit(patr, modernUnitTypes::artilery);
	}
	BattleModeling battle(army1, army2);
	battle();
	return 0;
}