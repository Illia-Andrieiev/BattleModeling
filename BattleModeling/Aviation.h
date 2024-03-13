#pragma once
#include"Unit.h"
class Aviation:public Unit
{
	double aviationDamagekoef = 0; /// Multiply 
public:
	Aviation(char name[256], double power, double viability);
};

