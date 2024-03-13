#include<iostream>
#include"Item.h"
#include"Army.h"
using namespace std;
int main() {
	Power p1(10, 21, 43, 5);
	Power p2(2, 3, 4, 5);
	Power p3 = p1 + p2;
	Power p4 = p1 * p2;
	cout << p1.artileryPowerKoef << " " << p1.aviationPowerKoef << " " << p1.infantryPowerKoef << " " << p1.vehicklePowerKoef << endl;
	cout << p2.artileryPowerKoef << " " << p2.aviationPowerKoef << " " << p2.infantryPowerKoef << " " << p2.vehicklePowerKoef << endl;
	cout << p3.artileryPowerKoef << " " << p3.aviationPowerKoef << " " << p3.infantryPowerKoef << " " << p3.vehicklePowerKoef << endl;
	cout << p4.artileryPowerKoef << " " << p4.aviationPowerKoef << " " << p4.infantryPowerKoef << " " << p4.vehicklePowerKoef << endl;

	Army army;
	char name[256] = "name1";
	
	Aviation fighter(name, 12,212);
	return 0;
}