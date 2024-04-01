#include "BattleModeling.h"
#include <thread>
BattleModeling::BattleModeling(ModernArmy& army1, ModernArmy& army2) {
	this->army1 = army1;
	this->army2 = army2;
}
void BattleModeling::setLapSupplies(Supply& supply) {
	this->lapSupplies = supply;
}
Supply BattleModeling::getLapSupplies() const{
	return lapSupplies;
}
void BattleModeling::battleLap() {
	std::thread army1Thread([&]() {army1.attackArmy(army2);});
	army2.attackArmy(army1);
	army1Thread.join();
	std::cout << "army1 viability: "<<army1.countViability() << std::endl << army1.toString();
	std::cout << "army2: viability: " << army2.countViability() << std::endl << army2.toString();
}
void BattleModeling::operator()() {
	ModernArmy army1, army2, reinF1,reinF2;
	army1 = this->army1;
	army2 = this->army2;
	reinF1 = this->army1Reinforcements;
	reinF2 = this->army2Reinforcements;
	ModernCircumstance summaryCirc = getSummCircumstance();
	army1.applyCircumstance(summaryCirc);
	army2.applyCircumstance(summaryCirc);
	army1.applyItems();
	army2.applyItems();
	army1.countViability();
	army2.countViability();
	while (army1.getViability() > 0 && army2.getViability() > 0) {
		battleLap();
		system("pause");
	}
}
ModernCircumstance BattleModeling::getSummCircumstance() {
	modern::ModernPowerCoef coef;
	ModernCircumstance summary(coef, std::string("Summary"));
	for (ModernCircumstance circ : circumstances) {
		summary.setPowerChanges(summary.getPowerChanges() * circ.getPowerChanges());
	}
	return summary;
}
void BattleModeling::addCircumstance(ModernCircumstance& circ) {
	circumstances.push_back(circ);
}