// Ejercicio 1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib>
#include<stdlib.h>
#include <ctime>
#include<Windows.h>
#include <cctype>



using namespace std;
//Atributos de los enemigos
int enemyHP1 = 100, enemyHP2 = 300;
string enemyName1 = "Agente", enemyName2 = "006";
bool enemyisAlive1 = true, enemyisAlive2 = true;
int enemyAttack1 = 0, enemyAttack2 = 0;
string name;


//Atributos del heroe
string heroName;
int heroDamage;
int heroDamage2;
int heroHP = 450;
bool heroisAlive = true;
int espadaAttack = 0;
int magiaAttack = 0;
int contadorMagia = 3;
int contadorLife = 2;
int heroAttack;
int paqueteMedico = 200;
string cura;

void gameStart() {

	cout << "Un " << enemyName1 << " con " << enemyHP1 << " de puntos de vida y " << enemyName2 << " con " << enemyHP2 << " de puntos de vida, acaban de aparecer \n";
	cout << "Como se llama el heroe? ";
	cin >> heroName;
	cout << "El nombre del heroe es: \n" << heroName << "\n";
}
void wichEnemy() {
	cout << "A que enemigo deseas atacar? \n";
	if (enemyisAlive1) {
		cout << "[1] Agente  \n";
	}

	if (enemyisAlive2) {
		cout << "[2] 006  \n";
	}
	cin >> name;

	cout << "Con que deseas atacar?  \n";
	if (enemyisAlive1 || enemyisAlive2) {
		cout << "[1] Laser  \n";

	}
	if (contadorMagia > 0) {
		cout << "[2] Lanza granadas  \n";

	}

	cin >> heroAttack;

}
void enemyStatus(string enemyName, int& enemyHP, bool& enemyisAlive) {
	if (enemyHP <= 0)
	{
		cout << enemyName << " Ha muerto \n";
		enemyisAlive = false;

	}
	else {
		cout << "Al enemigo " << enemyName << " le quedan " << enemyHP << " Puntos de vida  \n";
		enemyisAlive = true;
	}

}
int battleAttack() {

	enemyAttack1 = 1 + rand() % 61;
	enemyAttack2 = 30 + rand() % 99;
	return enemyAttack1, enemyAttack2;
}
void battle(int& enemyHP) {
	if (heroAttack == 1) {
		heroAttack = espadaAttack;
		espadaAttack = 10 + rand() % 46;
		enemyHP = enemyHP - espadaAttack;

	}
	if (heroAttack == 2) {
		heroAttack = magiaAttack;
		magiaAttack = 70 + rand() % 121;
		enemyHP = enemyHP - magiaAttack;
		contadorMagia = contadorMagia - 1;

		if (contadorMagia == 0) {
			cout << "Ya no tienes ataques de lanza granadas\n";
		}

	}
	battleAttack();

}
void enemyAttacksBack(string enemyName, int& enemyAttack) {
	if (heroHP <= 0) {
		heroHP = 0;
		cout << "El enemigo " << enemyName << " te ha matado \n";
		heroisAlive = false;
		cout << "Game Over \n";
	}
	else {
		cout << "El enemigo " << enemyName << " te ha hecho un ataque de " << enemyAttack << " puntos de danyo, te quedan " << heroHP << " puntos de vida \n";
	}
	if (heroisAlive && heroHP <= 100 && contadorLife > 0) {
		cout << "Tu vida esta baja. Deseas curarte? \n";
		cout << "[Y] si  \n";
		cout << "[N] no  \n";

		cin >> cura;
		cura = toupper('y');
		//cura = (char)toupper('n');
		if (contadorLife == 0) {
			cout << "Ya no tienes mas paquetes medicos\n";
		}
		contadorLife = contadorLife - 1;
		if (cura == "Y") {
			heroHP = heroHP + paqueteMedico;
			cout << "Recuperaste " << paqueteMedico << " de puntos de vida, ahora te quedan " << heroHP << " de puntos de vida \n";

		}
		else if (cura == "N") {

			cout << "No recuperaste vida \n";
		}
	}
}
void startbattle(string name, bool& enemyisAlive, int& enemyAttack) {
	if (name == "1") {
		if (enemyisAlive1 == true) {
			battle(enemyHP1);
			enemyStatus(enemyName1, enemyHP1, enemyisAlive1);

			if (enemyisAlive1) {
				//Ataca al héroe
				heroHP = heroHP - enemyAttack1;
				enemyAttacksBack(enemyName1, enemyAttack1);

			}
		}
	}

	if (name == "2") {
		if (enemyisAlive2 == true) {
			battle(enemyHP2);
			enemyStatus(enemyName2, enemyHP2, enemyisAlive2);

			if (enemyisAlive2) {
				//Ataca al héroe
				heroHP = heroHP - enemyAttack2;
				enemyAttacksBack(enemyName2, enemyAttack2);

			}
		}
	}
}


int main()
{
	gameStart();
	srand(time(NULL));
	while (enemyisAlive1 == true || enemyisAlive2 == true && heroisAlive == true) {

		if (enemyisAlive1 == true || enemyisAlive2 == true && heroisAlive == true) {
			wichEnemy();
			startbattle(name, enemyisAlive1, enemyAttack1);
		}

		if (heroHP <= 0) {
			break;
		}
	}

}


