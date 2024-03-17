#include "Army.h"
#include<typeinfo>
Army::Army() {
	for (int i = 0; i < 4; i++)
		positionOfLastAlive[i] = -1;
}
void countPower();
void addUnit(ModernUnit& unit, modernUnitTypes type);