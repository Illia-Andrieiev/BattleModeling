#include<iostream>
#include"Item.h"
#include"Army.h"
#include<concepts>
#include<typeinfo>
class A {
public:
	void print() {
		std::cout << "1";
	}
	int a = 1;
};
class B :public A {
public:
	double b = 2;
	void print() {
		std::cout << "2";
	}
};
using namespace std;
int main() {
	//Power p1(10, 21, 43, 5);
	//Power p2(2, 3, 4, 5);
	//Power p3 = p1 + p2;
	//Power p4 = p1 * p2;
	//cout << p1.artileryPowerKoef << " " << p1.aviationPowerKoef << " " << p1.infantryPowerKoef << " " << p1.vehicklePowerKoef << endl;
	//cout << p2.artileryPowerKoef << " " << p2.aviationPowerKoef << " " << p2.infantryPowerKoef << " " << p2.vehicklePowerKoef << endl;
	//cout << p3.artileryPowerKoef << " " << p3.aviationPowerKoef << " " << p3.infantryPowerKoef << " " << p3.vehicklePowerKoef << endl;
	//cout << p4.artileryPowerKoef << " " << p4.aviationPowerKoef << " " << p4.infantryPowerKoef << " " << p4.vehicklePowerKoef << endl;

	//Army army;
	//char name[256] = "name1";
	//
	////Aviation fighter(name, 12,212);
	////cout << fighter.getName() << endl;
	////fighter.getDamage(3);
	////army.addUnit(fighter);
	//for (int i = 0; i < army.aviation.size(); i++) {
	//	cout << army.aviation[i].getName();
	//}
	//for (int i = 0; i < army.artilery.size(); i++) {
	//	cout << army.artilery[i].getName()<<endl;
	//	army.artilery[i].getDamage(4);
	//}
	A* a = new B();
	if (std::same_as<A, B>) {
		a->print();
	}
	return 0;
}