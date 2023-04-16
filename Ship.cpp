#pragma once
#pragma comment(lib, "winmm")
#include "Ship.h"
#include <iostream>
#include<stdlib.h>
#include<Windows.h>
#include <cctype>
#include <mmsystem.h>
using namespace std;

//constructor
Ship::Ship(std::string pName, int pDistance, int pSpeed, int pNitro, /*int pHp,*/ int pAt ) {
	name = pName;
	distance = pDistance;
	speed = pSpeed;
	nitro = pNitro;
	//hp = pHp;
	at = pAt;
}


//getters
std::string Ship::getName() {
	return name;
}

int Ship::getDistance() {
	return distance;
}

int Ship::getSpeed() {
	return speed;
}

int Ship::getNitro() {
	return nitro;
}

//int Ship::getHp() {
//	return hp;
//}

int Ship::getAt() {
	return at;
}

//setters
void Ship::setName(std::string pName) {
	name = pName;
}

void Ship::setDistance(int pDistance) {
	distance = pDistance;
}

void Ship::setSpeed(int pSpeed) {
	speed = pSpeed;
}

void Ship::setNitro(int pNitro) {
	nitro = pNitro;
}

//void Ship::setHp(int pHp) {
//	hp = pHp;
//}
void Ship::setAt(int pAt) {
	at = pAt;
}

//METHODS
void Ship::printStats() {

	std::cout << "Es el turno de " << getName() << std::endl;
}

void Ship::calculateDistance() {
	distance = getDistance() + getSpeed() * 100;
}

void Ship::tirarDado() {
	if (getName() == "\033[33mAla X\033[0m") {
		cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "+                                        +" << endl;
		cout << "+ Ahora es el turno de " << getName() << "             +" << endl;
		cout << "+                                        +" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
	}
	else {
		cout << "++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "+                                          +" << endl;
		cout << "+ Ahora es el turno de " << getName() << "            +" << endl;
		cout << "+                                          +" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}
}

void Ship::turdoPlayer() {
	if (getName() == "\033[33mAla X\033[0m") {
		cout << getName() << " ha recorrido " << getDistance() << " metros con una velocidad de " << getSpeed() << " Km/h." << endl;
	}
	else {
		cout << getName() << " ha recorrido " << getDistance() << " metros con una velocidad de " << getSpeed() << " Km/h." << endl;
	}
}

int Ship::attack() {
	char attacks;
	int attackRandom = 0; 

		if (getName() == "\033[33mAla X\033[0m"){
			cout << "Tu enemigo te tiene en la mira, Cuidado!  \n";
			Sleep(1500);
			bool opening = PlaySound(TEXT("TIE Fighter Laser Blast2.wav"), NULL, SND_SYNC);
			attackRandom = rand() % 2;
			if (attackRandom == 0) {
				cout << "ha fallado. Lograste escapar " << endl;
			}
			else {
				bool opening = PlaySound(TEXT("TIE Fighter Laser Blast3.wav"), NULL, SND_SYNC);
				//distance = getDistance() / 2;
				cout << "Te ha dado! " << endl;
				setDistance(getDistance() / 2);
				setSpeed(getSpeed() / 2);
				//setAt(getAt() - 1);
			}

			//setDistance(getDistance() / 2);
			//setSpeed(getSpeed() / 2);

			setAt(getAt() - 1);
		}
		if (getName() == "\x1b[91mCaza TIE\x1b[0m") {

			cout << "\033[33mTu enemigo se está alejando, ¿Quieres lanzar un ataque? (s/n)\033[0m \n";
			cin >> attacks;
			if (attacks == 's') {

				//ship1.getAt() - 1;
				bool opening = PlaySound(TEXT("X-WingLaserBlastSound.wav"), NULL, SND_SYNC);
				attackRandom = rand() % 2;
				if (attackRandom == 0) {
					cout << "has fallado. Tu enemigo se ha escapando " << endl;
				}
				else {
					bool opening = PlaySound(TEXT("TIE fighter crash.wav"), NULL, SND_SYNC);
					//distance = getDistance() / 2;
					cout << "Le has dado! " << endl;
					setDistance(getDistance() / 2);
					setSpeed(getSpeed() / 2);
					//setAt(getAt() - 1);
				}

			}//etDistance(getDistance() / 2);

		}

	return 0;
}
