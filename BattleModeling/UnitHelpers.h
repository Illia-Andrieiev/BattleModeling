#pragma once
/// Represent how much unit influent on foe`s army
namespace unitHelpers {
	struct ModernPowerCoef {
		double aviationDamagekoef; /// Multiply default damage to aviation 
		double infantryDamagekoef; /// Multiply default damage to infantry 
		double vehickleDamagekoef; /// Multiply default damage to armored vehickles 
		double artileryDamagekoef; /// Multiply default damage to artilery
		ModernPowerCoef() {
			this->artileryDamagekoef = 1;
			this->aviationDamagekoef = 1;
			this->infantryDamagekoef = 1;
			this->vehickleDamagekoef = 1;
		}
		ModernPowerCoef(double aviationDamagekoef, double infantryDamagekoef,
			double vehickleDamagekoef, double artileryDamagekoef) {
			if (aviationDamagekoef < 0)
				aviationDamagekoef = 1;
			if (infantryDamagekoef < 0)
				infantryDamagekoef = 1;
			if (vehickleDamagekoef < 0)
				vehickleDamagekoef = 1;
			if (artileryDamagekoef < 0)
				artileryDamagekoef = 1;
			this->artileryDamagekoef = artileryDamagekoef;
			this->aviationDamagekoef = aviationDamagekoef;
			this->infantryDamagekoef = infantryDamagekoef;
			this->vehickleDamagekoef = vehickleDamagekoef;
		}
		ModernPowerCoef operator +(ModernPowerCoef& p2) {
			return ModernPowerCoef(aviationDamagekoef + p2.aviationDamagekoef, infantryDamagekoef + p2.infantryDamagekoef,
				vehickleDamagekoef + p2.vehickleDamagekoef, artileryDamagekoef + p2.artileryDamagekoef);
		}
		ModernPowerCoef operator *(ModernPowerCoef& p2) {
			return ModernPowerCoef(aviationDamagekoef * p2.aviationDamagekoef, infantryDamagekoef * p2.infantryDamagekoef,
				vehickleDamagekoef * p2.vehickleDamagekoef, artileryDamagekoef * p2.artileryDamagekoef);
		}
		ModernPowerCoef operator *(ModernPowerCoef p2) {
			return ModernPowerCoef(aviationDamagekoef * p2.aviationDamagekoef, infantryDamagekoef * p2.infantryDamagekoef,
				vehickleDamagekoef * p2.vehickleDamagekoef, artileryDamagekoef * p2.artileryDamagekoef);
		}
	};
	struct Cycling {
		int cyclesToReplenishment; /// Cycles of modeling, in which unit active
		int cyclesToActivation; /// Cycles of modeling, in which unit active
		int currentCycle;
		bool isActive;
		Cycling(int cyclesToReplenishment, int cyclesToActivation, bool isActive) {
			this->currentCycle = 0;
			this->cyclesToActivation = cyclesToActivation;
			this->cyclesToReplenishment = cyclesToReplenishment;
			this->isActive = isActive;
		}
		Cycling() {
			this->currentCycle = 0;
			this->cyclesToActivation = 2;
			this->cyclesToReplenishment = 10;
			this->isActive = true;
		}
	};
	enum unitTypes {
		artilery,
		aviation,
		armoredVehickle,
		infantry
	};
}