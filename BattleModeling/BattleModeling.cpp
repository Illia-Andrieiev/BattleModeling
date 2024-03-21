#include "BattleModeling.h"
#include <thread>
BattleModeling::BattleModeling(ModernArmy& army1, ModernArmy& army2) {
	this->army1 = army1;
	this->army2 = army2;
}
void BattleModeling::battleLap() {
	std::thread army1Thread([&]() {army1.attackArmy(army2);});
	army2.attackArmy(army1);
	army1Thread.join();
	std::cout << "army1 viability: "<<army1.countViability() << std::endl << army1.toString();
	std::cout << "army2: viability: " << army2.countViability() << std::endl << army2.toString();
}
void BattleModeling::operator()() {
	army1.countViability();
	army2.countViability();
	while (army1.getViability() > 0 && army2.getViability() > 0) {
		battleLap();
		system("pause");
	}
}