#pragma once
#include "Unit.h"
///Unit with morality
class MoralUnitTest;
class MoralUnit :public Unit
{
	friend class MoralUnitBuilder;
	friend class MoralUnitTest;
	friend class FileManager;
	double morality; ///< Units morality
	double rateOfMoralityChanges; ///< Represent rate of morality droping
	const int TYPE_ID = 1; ///< TYPE ID
	void attackUnitType(Unit& fortification, double& damage, int& posFirstAlive, std::vector<Unit*>& units) override;
	double determinePower() override;
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
	std::shared_ptr<MoralUnit> unit;
public:
	MoralUnitBuilder();
	virtual void reset() override;
	virtual std::shared_ptr<Unit> getResult() override;
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
class MoralUnitTest {
	MoralUnitBuilder builder;
	void isEqualTest();
	void takeDamageTest();
	void cloneTest();
	void createTest();
	void attackUnitTypeTest();
public:
	MoralUnitTest();
	void test();
};