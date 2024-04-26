#pragma once
#include "Unit.h"
///Unit with morality
class MoralUnit :public Unit
{
	friend class MoralUnitBuilder;
	friend class FileManager;
	double morality; ///< Units morality
	double rateOfMoralityChanges; ///< Represent rate of morality droping
	const int TYPE_ID = 1; ///< TYPE ID
	void attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<Unit*>& units) override;
	double determinePower(double minPower, double maxPower) override;
public:
	virtual int getTypeID() override;
	MoralUnit();
	bool isEqual(Unit* unit) override;
	MoralUnit& operator = (const MoralUnit& unit);
	void setMorality(double morality);
	double getMorality() const;
	void takeDamage(double& damage) override;
	void updateCycle() override;
	std::string toString() override;
	MoralUnit* clone() override;
	MoralUnit* create() override;
};
///Concrete MoralUnit builder
class MoralUnitBuilder :public BaseUnitBuilder {
private:
	MoralUnit unit;
public:
	MoralUnitBuilder();
	virtual void reset();
	virtual MoralUnit getResult();
	virtual MoralUnitBuilder* setName(const std::string& name) override;
	virtual MoralUnitBuilder* addItem(const Item& item) override;
	virtual MoralUnitBuilder* setPowerAndViability(double minPower, double maxPower, double viability) override;
	virtual MoralUnitBuilder* setFortificationTarget(bool fortificationTarget) override;
	virtual MoralUnitBuilder* setTypes(unitHelpers::unitTypes type, unitHelpers::unitTypes priorityTarget) override;
	virtual MoralUnitBuilder* setPowerCoef(const std::map<unitHelpers::unitTypes, double>& powerCoef) override;
	virtual MoralUnitBuilder* setCycling(const unitHelpers::Cycling& cycling) override;
	virtual MoralUnitBuilder* setMorality(double morality, double rateOfMoralityChanges);
	virtual MoralUnitBuilder* setArmor(double armor, bool isRenovate) override;
};