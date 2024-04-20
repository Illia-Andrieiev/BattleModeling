#pragma once
template<typename T>
class Cloneable
{
public:
	virtual T clone() = 0;
};
template<typename T>
class Prototype
{
public:
	virtual T create() = 0;
};
