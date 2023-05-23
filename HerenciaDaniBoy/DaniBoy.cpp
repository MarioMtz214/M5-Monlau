#pragma once
#include "DaniBoy.h"
#include <iostream>


using namespace std;


//constructor
DaniBoy::DaniBoy(std::string pName, int pLife, bool pAttack) {
	name = pName;
	life = pLife;
	attack = pAttack;
}


//getters
std::string DaniBoy::getName() {
	return name;
}

int DaniBoy::getLife() {
	return life;
}

bool DaniBoy::getAttack() {
	return attack;
}


//setters
void DaniBoy::setName(std::string pName) {
	name = pName;
}

void DaniBoy::setLife(int pLife) {
	life = pLife;
}

void DaniBoy::setAttack(bool pAttack) {
	attack = pAttack;
}


//METHODS
//void DaniBoy::inicio() {
//	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
//	cout << "+          Hoy ha sido un dia en el cole muy estresante para " << getName() << "       +" << endl;
//	cout << "+          Ayudalo a llegar a salida sin toparce con nadie               +" << endl;
//	cout << "+          Apara que pueda llegar felizmente a su casa                   +" << endl;
//	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
//	system("pause");
//	system("cls");
//}