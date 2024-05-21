#pragma once
/// Interface for clone method
template<typename T>
class Cloneable
{
public:
	virtual T clone() const = 0;
};
/// Interface for create method from Prototype pattern
template<typename T>
class Prototype
{
public:
	virtual T create() const  = 0;
};
