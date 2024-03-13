#pragma once
#include<string>
/// Represent how much unit influent on foe`s army
struct Power {
	double infantryPowerKoef; 
	double aviationPowerKoef; 
	double artileryPowerKoef; 
	double vehicklePowerKoef;
	Power(double infantryPowerKoef,double aviationPowerKoef,
		double artileryPowerKoef,double vehicklePowerKoef) {
		this->artileryPowerKoef = artileryPowerKoef;
		this->aviationPowerKoef = aviationPowerKoef;
		this->vehicklePowerKoef = vehicklePowerKoef;
		this->infantryPowerKoef = infantryPowerKoef;
	}
	Power() {
		this->artileryPowerKoef = 0;
		this->aviationPowerKoef = 0;
		this->vehicklePowerKoef = 0;
		this->infantryPowerKoef = 0;
	}
	Power operator +(Power& power2) {
		return Power(power2.infantryPowerKoef + infantryPowerKoef, power2.aviationPowerKoef + aviationPowerKoef,
			power2.artileryPowerKoef + artileryPowerKoef, power2.vehicklePowerKoef + vehicklePowerKoef);
	}
	Power operator *(Power& power2) {
		return Power(power2.infantryPowerKoef * infantryPowerKoef, power2.aviationPowerKoef * aviationPowerKoef,
			power2.artileryPowerKoef * artileryPowerKoef, power2.vehicklePowerKoef * vehicklePowerKoef);
	}
};
/// Represent items, that can be equiped by units
/*!
* Change unit`s power once on modeling start. adds powerChanges to the unit's power. Can increase or decrease.
*/
class Item
{
private:
	char name[256]; /// Item name
	Power powerChanges; /// Add to unit`s power. Parameters can be < 0
	double changeViability; /// Add to unit`s viability. Can be < 0
public:
	Item(Power& powerChanges, char name[256], double changeViability);
	Power getPowerChanges() const;
};

