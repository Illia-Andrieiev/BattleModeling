#pragma once
/// Represent how much unit influent on foe`s army
namespace unitHelpers {
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