// BlackJackBackUpII.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
//Variables de cartas
int corazones[13];
int diamantes[13];
int picas[13];
int treboles[13];
//bool gameOver;
const int MAX_CARTAS = 52;
int baraja[MAX_CARTAS];

//Variables del jugador
bool lose1 = false;
string player1;
int puntosPlayer1 = 0;
int opcion = 0;
char jugarDeNuevo;

//Variables del crupier
string player2 = "Crupier";
int puntosPlayer2 = 0;

// Empieza el juego
void gameStart() {
	system("Color E");
	cout << "Bienvenido al Black Jack \n";
	cout << "Cual es tu nombre? \n";
	cin >> player1;
	cout << "Hola " << player1 << "\n";
	cout << "Vamos a empezar! \n";
}

//inicializar array
void inicializaArray(int(&pArray)[13]) {
	for (int i = 0; i < 13; i++) {
		pArray[i] = 1;
	}
}

// Función para inicializar la baraja de cartas
void repartirCartas(int& puntos) {
	bool disponible = true;
	int numCarta;
	string tipoPalo;
	while (disponible)
	{
		int palo = rand() % 4;
		numCarta = 1 + rand() % 13;

		switch (palo + 1)
		{
		case 1:
			if (corazones[numCarta] == 1) {
				corazones[numCarta] = 0;
				tipoPalo = "corazones";
				disponible = false;
			}
			break;
		case 2:
			if (diamantes[numCarta] == 1) {
				diamantes[numCarta] = 0;
				tipoPalo = "diamantes";
				disponible = false;
			}
			break;
		case 3:
			if (treboles[numCarta] == 1) {
				treboles[numCarta] = 0;
				tipoPalo = "treboles";
				disponible = false;
			}
			break;
		case 4:
			if (picas[numCarta] == 1) {
				picas[numCarta] = 0;
				tipoPalo = "picas";
				disponible = false;
			}
			break;
		default:
			break;
		}

	}
	switch (numCarta) {
	case 1:
		if (puntos == puntosPlayer1) {
			cout << "Ha salido un A de " << tipoPalo << "\n";
			cout << "Que valor quieres que tenga ? [1] para 1 / [2] para 11 \n";
			cin >> opcion;
			if (opcion == 1) {
				cout << "Tu A es un 1";
				numCarta = 1;
				puntos += numCarta;
			}
			else {
				cout << "Tu A es un 11";

				numCarta = 11;
				puntos += numCarta;
			}
		}
		else {
			if (puntos == puntosPlayer2 && puntosPlayer2 <= 10) {
				cout << "Ha salido un A (11) ";
				numCarta = 11;
				puntos += numCarta;
			}
			else {
				cout << "Ha salido un A (1) ";
				numCarta = 1;
				puntos += numCarta;
			}
		}

		break;
	case 11:
		cout << "Ha salido una J ";
		numCarta = 10;
		puntos += numCarta;
		break;
	case 12:
		cout << "Ha salido una Q ";
		numCarta = 10;
		puntos += numCarta;
		break;
	case 13:
		cout << "Ha salido una K ";
		numCarta = 10;
		puntos += numCarta;
		break;

	default:
		cout << "Ha salido un " << numCarta;
		puntos += numCarta;
		break;
	}

	if (puntos == puntosPlayer2) {
		//cout << "-----Banca----- \n";
		cout << " de " << tipoPalo << "\n";
		cout << "El Crupier tiene " << puntos << " puntos\n";
	}
	else {
		//cout << "-----Jugador----- \n";
		cout << " de " << tipoPalo << "\n";
		cout << "Tienes " << puntos << " puntos\n";
	}

}

void whoWins() {
	if (puntosPlayer1 > 21 || puntosPlayer2 > puntosPlayer1 && puntosPlayer2 < 21) {
		cout << "HAS PERDIDO! \n";
	}
	else if (puntosPlayer1 == puntosPlayer2) {
		cout << "EMPATE! \n";
	}
	else if (puntosPlayer1 == 21 || puntosPlayer2 < puntosPlayer1) {
		cout << "Blackjack! HAS GANADO! \n";
	}
	else if (puntosPlayer2 > 21 && puntosPlayer1 < 21) {
		cout << "El Crupier pierde  y tu ganas! \n";
	}
	else if (puntosPlayer2 == 21 || puntosPlayer2 > puntosPlayer1 && puntosPlayer2 < 21) {
		cout << "LA CASA GANA! \n";
	}
}

void otraCarta() {

	if (puntosPlayer2 < 21) {
		repartirCartas(puntosPlayer2);
	}
}

int playAgain() {
	cout << "Quieres jugar de nuevo? (s/n): ";
	cin >> jugarDeNuevo;
	puntosPlayer1 = 0;
	puntosPlayer2 = 0;
	if (jugarDeNuevo == 'n') {
		cout << "Hasta luego!";
		exit(-1);
	}
}

int play() {
	inicializaArray(corazones);
	inicializaArray(diamantes);
	inicializaArray(treboles);
	inicializaArray(picas);
	do
	{
		cout << "-----Jugador----- \n";
		repartirCartas(puntosPlayer1);
		repartirCartas(puntosPlayer1);

		char decision;
		while (puntosPlayer1 < 21)
		{
			cout << "Quieres otra carta? (s/n): ";
			cin >> decision;

			if (decision == 's')
			{
				repartirCartas(puntosPlayer1);
				if (puntosPlayer1 > 21) {
					lose1 = true;
					cout << "YOU LOSE! \n";
					if (lose1 == true) {
						playAgain();
						play();
						exit(-1);
					}
				}
			}
			else
			{
				break;
			}
		}
		cout << "-----Banca----- \n";
		repartirCartas(puntosPlayer2);
		repartirCartas(puntosPlayer2);
		otraCarta();
		whoWins();
		playAgain();

	} while (jugarDeNuevo == 's');

	return 0;
}

int main() {
	srand(time(NULL));
	gameStart();
	play();
}