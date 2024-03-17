#pragma once
template<typename T>
class Clonable
{
public:
	virtual T clone() = 0;
};

