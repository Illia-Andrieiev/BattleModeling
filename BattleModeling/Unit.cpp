#include "Unit.h"
/// Return is unit alive
bool Unit::isAlive() const{
	return alive;
}
/// Constructor
Unit::Unit(char name[256], Power& power, double viability) {
	this->power = power;
	for (int i = 0; i < 256; i++)
		this->name[i] = name[i];
	this->viability = viability;
	this->alive = true;
}
/// Constructor
Unit::Unit(char name[256], Power& power, double viability, std::vector<Item>& items) {
	this->power = power;
	for (int i = 0; i < 256; i++)
		this->name[i] = name[i];
	this->viability = viability;
	this->alive = true;
	this->items = items;
}
/// Decrease viability on damage. If viability <= 0 set alive = false
void Unit::getDamage(double damage) {
	this->viability -= damage;
	if (viability <= 0)
		alive = false;
}
Power Unit::getPower() const {
	return power;
}