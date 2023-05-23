#pragma once
#include "DaniBoyEnemigoFinal.h"
#include "DaniBoy.h"
#include <iostream>


using namespace std;


EnemigoFinal::EnemigoFinal(std::string pName,
											int pLife,
											int pAttack,
											bool pAttackEsp) : DaniBoy(pName,
																		pLife,
																		pAttack) {attackEsp = pAttackEsp;}




//GETTERS AND SETTERS
bool EnemigoFinal::getAttackEsp() {
	return attackEsp;
}

void EnemigoFinal::setAttackEsp(bool pAttackEsp) {
	attackEsp = pAttackEsp;
}


//METODOS PROPIOS
//void EnemigoFinal::examenEnemigo() {
//
//}