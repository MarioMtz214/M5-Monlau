// Ejercicio 1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib>
#include<stdlib.h>
#include <ctime>
#include<Windows.h>
#include <cctype>



using namespace std;
//Atribudos del enemigo 1
int enemyHP = 100;
string enemyName1 = "Agente";
bool enemyisAlive = true;
int enemyDamage = 0;
string enemyName;

//Atribudos del enemigo 2
int enemyHP2 = 300;
string enemyName2 = "006";
bool enemyisAlive2 = true;
int enemyDamage2 = 0;

//Atributos del heroe
string heroName;
int heroDamage;
int heroDamage2;
int heroHP = 400;
bool heroisAlive = true;
int espadaAttack = 0;
int magiaAttack = 0;
int contadorMagia = 3;
int contadorLife = 2;
int heroAttack;
int paqueteMedico = 200;
string cura;



int main()
{
	bool opening = PlaySound(TEXT("007.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);

	cout << "Un " << enemyName1 << " con " << enemyHP << " de puntos de vida y " << enemyName2 << " con " << enemyHP2 << " de puntos de vida, acaban de aparecer \n";
	cout << "Como se llama el heroe? ";
	cin >> heroName;
	cout << "El nombre del heroe es: \n" << heroName << "\n";
	srand(time(NULL));
	while (enemyisAlive == true || enemyisAlive2 == true && heroisAlive == true) {
		/*system("cls");*/
		if (enemyisAlive == true || enemyisAlive2 == true && heroisAlive == true) {
			cout << "A que enemigo deseas atacar? \n";
			if (enemyisAlive) {
				cout << "[1] Agente  \n";
			}

			if (enemyisAlive2) {
				cout << "[2] 006  \n";
			}
			cin >> enemyName;

			cout << "Con que deseas atacar?  \n";
			if (enemyisAlive || enemyisAlive2) {
				cout << "[1] Laser  \n";

			}
			if (enemyisAlive || enemyisAlive2 && contadorMagia > 0) {
				cout << "[2] Lanza granadas  \n";
		
			}
			

			cin >> heroAttack;


			if (enemyName == "1") {
				if (enemyisAlive == true) {
					if (heroAttack == 1) {
						heroAttack = espadaAttack;
						espadaAttack = 10 + rand() % 36;
						enemyHP = enemyHP - espadaAttack;
						bool opening = PlaySound(TEXT("laser1.wav"), NULL, SND_SYNC);
					}
					if (heroAttack == 2) {
						heroAttack = magiaAttack;
						magiaAttack = 20 + rand() % 121;
						enemyHP = enemyHP - magiaAttack;
						contadorMagia = contadorMagia - 1;
						bool opening = PlaySound(TEXT("rocket3.wav"), NULL, SND_SYNC);
						if (contadorMagia == 0) {
							cout << "Ya no tienes ataques de lanza granadas\n";
						}

					}

					bool opening = PlaySound(TEXT("007.wav"), NULL, SND_ASYNC);

					enemyDamage = 1 + rand() % 71;
					enemyDamage2 = 50 + rand() % 111;

					if (enemyHP <= 0)
					{
						cout << enemyName1 << " Ha muerto \n";
						enemyisAlive = false;
					}
					else {
						cout << "Al enemigo " << enemyName1 << " le quedan " << enemyHP << " Puntos de vida  \n";
					}

					if (enemyisAlive) {
						//Ataca al héroe
						heroHP = heroHP - enemyDamage;

						if (heroHP <= 0) {
							heroHP = 0;
							cout << "El enemigo " << enemyName1 << " te ha matado \n";
							cout << "Game Over \n";
							heroisAlive = false;
						}
						else {
							cout << "El enemigo " << enemyName1 << " te ha hecho un ataque de " << enemyDamage << " puntos de danyo, te quedan " << heroHP << " puntos de vida \n";
						}
						if (heroisAlive && heroHP <= 100 && contadorLife > 0) {
							cout << "Tu vida esta baja. Deseas curarte? \n";
							cout << "[Y] si  \n";
							cout << "[N] no  \n";

							cin >> cura;
							cura = (char)toupper('y');
							if (contadorLife == 0) {
								cout << "Ya no tienes mas paquetes medicos\n";
							}
							contadorLife = contadorLife - 1;
							if (cura == "Y") {
								heroHP = heroHP + paqueteMedico;
								cout << "Recuperaste " << paqueteMedico << " de puntos de vida, ahora te quedan " << heroHP << " de puntos de vida \n";


							}
						}

					}
				}
			}

			if (enemyName == "2") {
				if (enemyisAlive2 == true) {
					if (heroAttack == 1) {
						heroAttack = espadaAttack;
						espadaAttack = 10 + rand() % 36;
						enemyHP2 = enemyHP2 - espadaAttack;
						bool opening = PlaySound(TEXT("laser1.wav"), NULL, SND_SYNC);
					}
					if (heroAttack == 2) {
						heroAttack = magiaAttack;
						magiaAttack = 20 + rand() % 121;
						enemyHP2 = enemyHP2 - magiaAttack;
						contadorMagia = contadorMagia - 1;
						bool opening = PlaySound(TEXT("rocket3.wav"), NULL, SND_SYNC);
						if (contadorMagia == 0) {
							cout << "Ya no tienes ataques de lanza granadas \n";
						}
					}
					bool opening = PlaySound(TEXT("007.wav"), NULL, SND_ASYNC);
					enemyDamage = 1 + rand() % 71;
					enemyDamage2 = 50 + rand() % 111;

					if (enemyHP2 <= 0)
					{
						cout << enemyName2 << " Ha muerto \n";
						enemyisAlive2 = false;
					}
					else {
						cout << "Al enemigo " << enemyName2 << " le quedan " << enemyHP2 << " Puntos de vida \n";
					}

					if (enemyisAlive2) {
						//Ataca al héroe

						heroHP = heroHP - enemyDamage2;


						if (heroHP <= 0) {
							heroHP = 0;
							cout << "El enemigo " << enemyName2 << " te ha matado \n";
							cout << "Game Over \n";
							heroisAlive = false;
						}

						else {
							cout << "El enemigo " << enemyName2 << " te ha hecho un ataque de " << enemyDamage2 << " puntos de danyo, te quedan " << heroHP << " puntos de vida\n";
						}
						if (heroisAlive && heroHP <= 100  && contadorLife > 0) {
							cout << "Tu vida esta baja. Deseas curarte? \n";
							cout << "[Y] si  \n";
							cout << "[N] no  \n";

							cin >> cura;
							cura = (char)toupper('y');
							if (contadorLife == 0) {
								cout << "Ya no tienes mas paquetes medicos\n";
							}
							contadorLife = contadorLife - 1;
							if (cura == "Y") {
								heroHP = heroHP + paqueteMedico;
								cout << "Recuperaste " << paqueteMedico << " de puntos de vida, ahora te quedan " << heroHP << " de puntos de vida \n";


							}
						}
						

					}
				}
			}
		}







	}

}




//cout << heroName << " ataca a " << enemyName << " y resta " << heroDamage << " depuntos de vida";