#pragma once
#include <iostream>
#include <windows.h>


class DaniBoy {

private:
	//DaniBoy
	std::string name;
	int life;
	bool attack;

public:
	//constructor
	DaniBoy(std::string pName, int pLife, bool pAttack);


	//getters
	std::string getName();
	int getLife();
	bool getAttack();

	//setters
	void setName(std::string pName);
	void setLife(int pLife);
	void setAttack(bool pAttack1);


	//METHODS
	void inicio();

};