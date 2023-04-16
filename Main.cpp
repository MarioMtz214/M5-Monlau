#pragma comment(lib, "winmm")
#include "Ship.h"
#include <iostream>
//acentos
#include <wchar.h>
#include <locale.h>
//numero aleatorio
#include <cstdlib>
#include <ctime>
//sonido
#include<stdlib.h>
#include<Windows.h>
#include <cctype>
#include <string>

using namespace std;

//Variables
int meta = 5000;
char jugarDeNuevo;
char useNitro;
int dado = 6;
double newSpeed = 0;
double newDistance = 0;
int nitroRandom = 0;
//int attackRandom = 0;
char playAgain;
char startPlay;
char attacks;


void escribirLetraPorLetra(std::string texto) {
	for (int i = 0; i < texto.length(); i++) {
		std::cout << texto[i];
		Sleep(50); // ajusta el tiempo de espera aquí para controlar la velocidad de escritura
	}
	std::cout << std::endl;
}

void gameIntro() {	
	SetConsoleOutputCP(65001);
	bool opening = PlaySound(TEXT("Star-Wars.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);
	Sleep(500);
	cout << " \033[33m       _______________    ____ \n"
	      "       /  ___/_  __/   |  / __ | \n"
		 "       | __ | / / / /| | / /_/ / \n"
		  "       ___/ // / / ___ |/ _, _/  \n"
		 "      /____//_/ /_/  |_/_/ |_|   \n"

		"    ____  ___  ______________    ______\n"
		"   / __ )/   |/_  __/_  __/ /   / ____/ \n"
		"  / __  / /| | / /   / / / /   / __/ \n"
		" / /_/ / ___ |/ /   / / / /___/ /___\n"
		"/_____/_/  |_/_/   /_/ /_____/_____/ \n"

		"    ____  ___    ____________\n"
		"   / __ |/   |  / ____/____/ \n"
		"  / /_/ / /| | / /   / __/ \n"
		" / _, _/ ___  / /___/ /___\n"
		"/_/ |_/ _/ |_| ____/_____/ \033[0m\n"
	    "  \n";


	system("pause");
	system("cls");

	std::string texto ="En Star Battle Race el primero que llegue a la meta gana, pero cuidado!\n"
		"Tus oponentes harán de todo para detenerte! \n";
	escribirLetraPorLetra(texto);

	Sleep(1000);
	cout << "Te atreves a intentarlo? (s/n): " << endl;
	cin >> startPlay;
	if (startPlay == 'n') {
		cout << "Hasta luego!";
		exit(-1);
	}
	else {
		Sleep(500);
		cout << "Preparados? " << endl;
		PlaySound(TEXT("X Wing Take off.wav"), NULL, SND_ASYNC);
		Sleep(3000);
		cout << "3 " << endl;
		Sleep(1000);
		cout << "2 " << endl;
		Sleep(1000);
		cout << "1 " << endl;
		Sleep(2000);
		cout << "GO! " << endl;
		bool opening = PlaySound(TEXT("BackgroundMusic2.wav"), NULL, SND_ASYNC);
	}
}

void turno(Ship& ship) {
	bool opening = PlaySound(TEXT("BackgroundMusic2.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);
	ship.tirarDado();
	dado = rand() % 6 + 1;

	cout << ship.getName() << " tira el dado y saca un... ";
	Sleep(2000);
	cout << dado << "!" << endl;

	newSpeed = ship.getSpeed() + dado;
	
	if (ship.getNitro() > 0 && ship.getName() == "\033[33mAla X\033[0m") {

		cout << "Desea usar nitro? (s/n): ";
		cin >> useNitro;

		if (tolower(useNitro) == 's') {
			nitroRandom = rand() % 2;
			if (nitroRandom == 0) {
				bool opening = PlaySound(TEXT("nitroFails.wav"), NULL, SND_SYNC);
				newSpeed /= 2;
				cout << "Se ha usado el nitro, pero ha fallado. La velocidad ahora es " << newSpeed << endl;
			}
			else {
				bool opening = PlaySound(TEXT("nitro1.wav"), NULL, SND_SYNC);
				newSpeed *= 2;
				cout << "Se ha usado el nitro! La velocidad ahora es " << newSpeed << endl;
			}
			ship.setNitro(ship.getNitro() - 1);
		}
	}

	if (ship.getName() == "\x1b[91mCaza TIE\x1b[0m" && ship.getNitro() > 0 && (dado == 4 || dado == 5 || dado == 6)) {

		nitroRandom = rand() % 2;
		if (nitroRandom == 0) {
			newSpeed /= 2;
			cout << ship.getName() << " ha usado el nitro, pero ha fallado. La velocidad ahora es " << newSpeed << endl;
		}
		else {
			newSpeed *= 2;
			cout << ship.getName() << " ha usado el nitro. La velocidad ahora es " << newSpeed << endl;
			bool opening = PlaySound(TEXT("nitro2.wav"), NULL, SND_SYNC);
		}
		ship.setNitro(ship.getNitro() - 1);
	}
	Sleep(500);
	ship.setSpeed(newSpeed);
};

void blasterAttack(Ship& ship1, Ship& ship2) {
	
		if (ship2.getDistance() > ship1.getDistance() /*&& ship1.getAt() > 0*/)
		{
			ship2.attack();
			ship2.turdoPlayer();
			bool opening = PlaySound(TEXT("BackgroundMusic2.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);
		}
		else 
		{
			if (ship1.getDistance() > ship2.getDistance() /*&& ship2.getAt() > 0*/) {
				ship1.attack();
				ship1.turdoPlayer();
				bool opening = PlaySound(TEXT("BackgroundMusic2.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);
			}
		}
}

void play(Ship& ship1, Ship& ship2) {

	do
	{
		turno(ship1);
		bool opening = PlaySound(TEXT("BackgroundMusic2.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);
		ship1.calculateDistance();
		ship1.turdoPlayer();
		Sleep(1000);
		turno(ship2);
		ship2.calculateDistance();

		ship2.turdoPlayer();
		blasterAttack(ship1, ship2);
		system("pause");
		system("cls");
		if (ship1.getDistance() >= meta && ship1.getDistance() > ship2.getDistance()) {
			cout << ship1.getName() << " ha ganado la carrera!" << endl;
			cout << "Feliciades!" << endl;
		}
		else if (ship2.getDistance() >= meta && ship2.getDistance() > ship1.getDistance()) {
			cout << ship2.getName() << " ha ganado la carrera!" << endl;
		}
		else {
			cout << "Es un empate!" << endl;
		}
	} while (ship1.getDistance() < meta && ship2.getDistance() < meta);
	

}

int restart() {
	cout << "Quieres jugar de nuevo? (s/n): ";
	cin >> playAgain;
	if (playAgain == 'n') {
		cout << "Hasta luego!";
		exit(-1);
	}
	system("cls");
	return 0;
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
		
	gameIntro();
	do
	{
		Ship ship1("\033[33mAla X\033[0m", 0, 0, 1, 1);
		Ship ship2("\x1b[91mCaza TIE\x1b[0m", 0, 0, 1, 1);
		
		play(ship1, ship2);
		restart();
		
	} while (playAgain == 's');

	return 0;
}