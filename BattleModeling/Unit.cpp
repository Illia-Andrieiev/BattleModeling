#include "Unit.h"
/// Return is unit alive
bool Unit::isAlive() const{
	return alive;
}
/// Constructor
Unit::Unit(std::string name, double power, double viability) {
	this->power = power;
	for (int i = 0; i<name.size() && i < 256; i++)
		this->name[i] = name[i];
	for (int i = name.size(); i < 256; i++)
		this->name[i] = ' ';
	this->viability = viability;
	this->alive = true;
	this->morality = 100;
}
/// Constructor
Unit::Unit(std::string name, double power, double viability, std::vector<Item>& items) {
	this->power = power;
	for (int i = 0; i < name.size()&& i < 256; i++)
		this->name[i] = name[i];
	for(int i = name.size(); i<256;i++)
		this->name[i] = ' ';
	this->viability = viability;
	this->alive = true;
	this->items = items;
	this->morality = 100;
}
/// Decrease viability on damage. If viability <= 0 set alive = false. Decrease damage on viability points
void Unit::takeDamage(double& damage) {
	this->viability -= damage;
	if (viability <= 0) {
		alive = false;
		damage = -viability;
	}
	else
		damage = 0;
}
double Unit::getBasePower() const {
	return power;
}
std::string Unit::getName() const{
	return std::string(name);
}
double Unit::getViability() const {
	return viability;
}
std::vector<Item> Unit::getItems() const {
	return items;
}
/// Add to unit`s viability and power appropriated parameters from item
void Unit::applyItems() {
	for (int i = 0; i < items.size();i++) {
		if (!items[i].isApply()) {
			items[i].apply();
			power += items[i].getBasePowerChanges();
			viability += items[i].getViabilityChanges();
		}
	}
}
void Unit::setMorality(double newMorality) {
	if (newMorality > 100) {
		morality = 100;
		return;
	}
	if (newMorality < 0) {
		morality = 0;
	}
	else
		morality = newMorality;
}
double Unit::getMorality() const {
	return morality;
}