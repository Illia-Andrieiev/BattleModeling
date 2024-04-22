#pragma once
#include<map>
/// Represent how much unit influent on foe`s army
namespace unitHelpers {
	enum unitTypes {
		artilery,
		aviation,
		armoredVehickle,
		infantry
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
		bool isEqual (const Cycling& other) const{
			return this->currentCycle == other.currentCycle && this->cyclesToActivation == other.cyclesToActivation &&
				this->cyclesToReplenishment == other.cyclesToReplenishment && this->isActive == other.isActive;
		}
	};

}