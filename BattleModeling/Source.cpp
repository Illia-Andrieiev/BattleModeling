#include<iostream>
#include"BattleModeling.h"


using namespace std;
int main() {
	Army army1;
	Army army2;
	army1.changeSupplies(9999999);
	army2.changeSupplies(9999999);
	string namesol("Snake");
	unitHelpers::Cycling soliderCycle(10, 2, true);
	unitHelpers::ModernPowerCoef soliderModernPowerCoef(0.05, 1, 0.15, 0.1);
	ModernUnit solider(namesol, 50, 100, false, soliderCycle, soliderModernPowerCoef);
	string nameavi("F-16");
	unitHelpers::Cycling aviCycle(8, 2, true);
	unitHelpers::ModernPowerCoef aviModernPowerCoef(1, 0.2, 0.8, 0.8);
	ModernUnit avi(nameavi, 300, 800, false, aviCycle, aviModernPowerCoef);
	string nametank("T-64 Bulat");
	unitHelpers::Cycling tankCycle(12, 1, true);
	unitHelpers::ModernPowerCoef tankModernPowerCoef(0.01, 1.3, 1.5, 0.5);
	ModernUnit tank(nametank, 200, 600, false, tankCycle, tankModernPowerCoef);
	string nameart("Caesar");
	string namepatr("Patriot");
	unitHelpers::Cycling artCycle(10, 0, true);
	unitHelpers::ModernPowerCoef artModernPowerCoef(0, 1.5, 1, 0.8);
	unitHelpers::ModernPowerCoef patrModernPowerCoef(2, 0.2, 0.3, 0.3);
	ModernUnit art(nameart, 300, 400, false, artCycle, artModernPowerCoef);
	ModernUnit patr(namepatr, 300, 450, false, artCycle, patrModernPowerCoef);
	/*for (int i = 0; i < 50; i++) {
		army1.addUnit(solider, modern::modernUnitTypes::infantry);
	}
	for (int i = 0; i < 65; i++) {
		army2.addUnit(solider, modern::modernUnitTypes::infantry);
	}
	for (int i = 0; i < 8; i++) { 
		army1.addUnit(avi, modern::modernUnitTypes::aviation);
	}
	for (int i = 0; i < 6; i++) {
		army2.addUnit(avi, modern::modernUnitTypes::aviation);
	}
	for (int i = 0; i < 10; i++) {
		army1.addUnit(tank, modern::modernUnitTypes::armoredVehickle);
	}
	for (int i = 0; i < 15; i++) {
		army2.addUnit(tank, modern::modernUnitTypes::armoredVehickle);
	}
	for (int i = 0; i < 15; i++) {
		army1.addUnit(art, modern::modernUnitTypes::artilery);
	}
	for (int i = 0; i < 10; i++) {
		army2.addUnit(art, modern::modernUnitTypes::artilery);
	}
	for (int i = 0; i < 8; i++) {
		army1.addUnit(patr, modern::modernUnitTypes::artilery);
	}
	for (int i = 0; i < 6; i++) {
		army2.addUnit(patr, modern::modernUnitTypes::artilery);
	}
	*/
	Unit* u = new ModernUnit(nameart, 12, 13, false, artCycle, artModernPowerCoef);
	std::cout<<u->toString()<<endl;
	{
		vector<Unit*> vecu;
		vecu.push_back(u);
		cout<<vecu[0]->toString()<<endl;
	}
	std::cout << u->toString() << endl;
	delete u;
	//BattleBuilder builder;
	//BattleModeling battle = builder.setArmy(army1, army2)->getResult();
	////cout << army1.countViability() << "  " << army2.countViability();
	//battle();
	return 0;
}