#pragma once
#include<map>
/// Represent how much unit influent on foe`s army
namespace unitHelpers {
	/// Units types
	enum unitTypes {
		artilery,
		aviation,
		armoredVehickle,
		infantry
	};
	///Cycling unit on battle field
	/*!
	*  Represent how much rounds unit stay active and unactive on battle field. Stores current round nomer.
	*/
	struct Cycling {
		int cyclesToReplenishment; ///< Cycles of modeling, in which unit active
		int cyclesToActivation; ///< Cycles of modeling, in which unit active
		int currentCycle; ///< Nomer of current cycle
		bool isActive; ///< Is unit active
		/// Constructor
		Cycling(int cyclesToReplenishment, int cyclesToActivation, bool isActive) {
			this->currentCycle = 0;
			this->cyclesToActivation = cyclesToActivation;
			this->cyclesToReplenishment = cyclesToReplenishment;
			this->isActive = isActive;
		}
		/// Constructor
		Cycling() {
			this->currentCycle = 0;
			this->cyclesToActivation = 2;
			this->cyclesToReplenishment = 10;
			this->isActive = true;
		}
		/// Is this Cycling equal to another
		bool isEqual(const Cycling& other) const {
			return this->currentCycle == other.currentCycle && this->cyclesToActivation == other.cyclesToActivation &&
				this->cyclesToReplenishment == other.cyclesToReplenishment && this->isActive == other.isActive;
		}
	};

}