#pragma once
#include "DaniBoy.h"
#include <iostream>


class EnemigoFinal : public DaniBoy
{
private:
	bool attackEsp;
public:
	//EnemigoFinal(std::string pName, int pLife, bool pAttack, bool pAttackEsp);

	
	EnemigoFinal(std::string pName, int pLife, int pAttack, bool pAttackEsp);

	bool getAttackEsp();

	void setAttackEsp(bool pAttackEsp);


	//void examen();
};

