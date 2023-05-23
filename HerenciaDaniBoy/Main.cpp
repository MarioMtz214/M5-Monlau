
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Sleep.hpp>
#include "DaniBoy.h"
#include "DaniBoyEnemigoFinal.h"
#include<Windows.h>
#include <cctype>


using namespace std;

const float boardWidth = 1398;
const float boardHeight = 1120;

char decision = ' ';
bool continuePlaying = true;
bool peleaTriggered = false;
bool showResponse = false;
bool firstTextDisplayed = false;
bool secondTextDisplayed = false;
bool castigado = false;
bool showCastigo = false;
bool resultadoExamen = false;
bool showHeart3 = true;
bool showHeart2 = true;
bool showHeart1 = true;
bool gameOver = false;
bool youWin = false;
bool enteredArea0 = false;
bool examenAprobado = true;
//int pringao1 = 1; //esto va en la clase
int examen = 0;
int preguntaActual = 1;

sf::Clock castigoTimer;
sf::Clock respuestaTimer;

bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
	return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

bool isInArea(const sf::Sprite& sprite, const sf::Vector2f& areaMin, const sf::Vector2f& areaMax) {
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	return spriteBounds.left >= areaMin.x && spriteBounds.left + spriteBounds.width <= areaMax.x &&
		spriteBounds.top >= areaMin.y && spriteBounds.top + spriteBounds.height <= areaMax.y;
}

int portada() {
	sf::RenderWindow windowPortada(sf::VideoMode(1398, 1120), "Portada");
	windowPortada.setFramerateLimit(10);
	sf::Event event;

	// Texturas y Sprites
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("portadaDani.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite backgroundSprite(backgroundTexture);

	// Textos
	sf::Font font;
	if (!font.loadFromFile("DePixelHalbfett.ttf")) {
		return EXIT_FAILURE;
	}

	sf::Text portadaText;
	portadaText.setFont(font);
	portadaText.setString("Presiona ENTER para continuar...");
	portadaText.setCharacterSize(30);
	portadaText.setFillColor(sf::Color(253, 239, 162));
	portadaText.setPosition(360, 670);

	bool isVisible = true;
	sf::Clock clock;
	float blinkingTime = 0.5f; // Tiempo de parpadeo en segundos

	while (windowPortada.isOpen()) {

		//PlaySound(TEXT("LavenderTown.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);
		PlaySound(TEXT("SMBOverworld.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);

		while (windowPortada.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				windowPortada.close();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				PlaySound(NULL, NULL, 0);
				windowPortada.close();
			}
		}

		// Obtener el tiempo transcurrido desde el inicio del parpadeo
		float elapsedTime = clock.getElapsedTime().asSeconds();

		// Alternar la visibilidad del texto según el tiempo transcurrido
		if (elapsedTime >= blinkingTime) {
			isVisible = !isVisible;
			clock.restart();
		}

		windowPortada.clear();
		windowPortada.draw(backgroundSprite);

		// Solo dibujar el texto si está visible
		if (isVisible) {
			windowPortada.draw(portadaText);
		}

		windowPortada.display();
	}

	return 0;
}

int grafico(DaniBoy& dani, EnemigoFinal& profe) {

	sf::RenderWindow window(sf::VideoMode(1398, 1120), "Dani Boy");
	window.setFramerateLimit(10);
	sf::Event event;

	//Texturas y Sprites
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Classroom.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite backgroundSprite(backgroundTexture);

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("dani.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite playerSprite(playerTexture);
	playerSprite.setPosition(634, 225);

	sf::IntRect rectSourceSprite(0, 0, 77, 99);
	playerSprite.setTextureRect(rectSourceSprite);

	sf::Texture corazonTexture1;
	if (!corazonTexture1.loadFromFile("corazon.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite corazonSprite1(corazonTexture1);
	corazonSprite1.setPosition(930, 960);

	sf::Texture corazonTexture2;
	if (!corazonTexture2.loadFromFile("corazon.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite corazonSprite2(corazonTexture2);
	corazonSprite2.setPosition(1040, 960);

	sf::Texture corazonTexture3;
	if (!corazonTexture3.loadFromFile("corazon.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite corazonSprite3(corazonTexture3);
	corazonSprite3.setPosition(1150, 960);

	sf::Texture examenTexture;
	if (!examenTexture.loadFromFile("fondoExamen.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite examenSprite(examenTexture);
	examenSprite.setPosition(350, 250);




	sf::Clock responseTimer;
	sf::Clock clock;
	const sf::Time frameTime = sf::seconds(0.5f / 10.0f);
	float speed = 150.0f;
	const float activationRange = 50.0f;


	//áreas de activación
	sf::FloatRect activationArea0(360, 170, 240, 180);//profesora
	sf::FloatRect activationArea1(450, 310, 200, 180);//pringao 1
	sf::FloatRect activationArea2(170, 550, 180, 150);//puerta salida
	sf::FloatRect activationArea3(280, 120, 180, 170);//pringao 3


	//Textos

	sf::Font font;
	if (!font.loadFromFile("DePixelHalbfett.ttf")) {
		return EXIT_FAILURE;
	}

	sf::Text text;
	text.setFont(font);
	text.setString("DANI BOY!");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color(253, 239, 162));
	text.setPosition(1150, 40);

	sf::Text tituloExText;
	tituloExText.setFont(font);
	tituloExText.setString("Examen de Java!");
	tituloExText.setCharacterSize(30);
	tituloExText.setFillColor(sf::Color(253, 239, 162));
	tituloExText.setPosition(550, 310);

	sf::Text preguntaExText;
	preguntaExText.setFont(font);
	preguntaExText.setCharacterSize(20);
	preguntaExText.setFillColor(sf::Color(253, 239, 162));

	sf::Text respuestaExText;
	respuestaExText.setFont(font);
	respuestaExText.setCharacterSize(20);
	respuestaExText.setFillColor(sf::Color(253, 239, 162));

	sf::Text resultadoExText;
	resultadoExText.setFont(font);
	resultadoExText.setCharacterSize(20);
	resultadoExText.setFillColor(sf::Color(253, 239, 162));

	sf::Text profeExText;
	profeExText.setFont(font);
	profeExText.setCharacterSize(20);
	profeExText.setFillColor(sf::Color(253, 239, 162));
	profeExText.setString("-Para poder irte tienes que hacer el \n examen");
	profeExText.setPosition(760, 90);

	sf::Text listoExText;
	listoExText.setFont(font);
	listoExText.setCharacterSize(20);
	listoExText.setFillColor(sf::Color(253, 239, 162));
	listoExText.setString("Estás listo para el examen? (s/n)");
	listoExText.setPosition(770, 165);

	sf::Text pringao1Text;
	pringao1Text.setFont(font);
	pringao1Text.setCharacterSize(20);
	pringao1Text.setFillColor(sf::Color(253, 239, 162));
	pringao1Text.setString("-Quieres saber un secreto?");
	pringao1Text.setPosition(760, 90);

	sf::Text pringao2Text;
	pringao2Text.setFont(font);
	pringao2Text.setCharacterSize(20);
	pringao2Text.setFillColor(sf::Color(253, 239, 162));
	pringao2Text.setString("-Profe! Ha olvidado revisar los deberes");
	pringao2Text.setPosition(760, 90);

	sf::Text molestarText;
	molestarText.setFont(font);
	molestarText.setCharacterSize(20);
	molestarText.setFillColor(sf::Color(253, 239, 162));
	molestarText.setString("Quieres molestar a pringao? (s/n)");
	molestarText.setPosition(770, 135);

	sf::Text salidaText;
	salidaText.setFont(font);
	salidaText.setCharacterSize(20);
	salidaText.setFillColor(sf::Color(253, 239, 162));
	salidaText.setString("Quieres salir de clase? (s/n)");
	salidaText.setPosition(770, 90);

	sf::Text daniText;
	daniText.setFont(font);
	daniText.setCharacterSize(20);
	daniText.setFillColor(sf::Color(253, 239, 162));

	sf::Text profeText;
	profeText.setFont(font);
	profeText.setCharacterSize(20);
	profeText.setFillColor(sf::Color(253, 239, 162));

	sf::Text are2Text;
	are2Text.setFont(font);
	are2Text.setCharacterSize(20);
	are2Text.setFillColor(sf::Color(253, 239, 162));

	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(90);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("Game Over!");
	gameOverText.setPosition(390, 470);

	sf::Text youWinText;
	youWinText.setFont(font);
	youWinText.setCharacterSize(100);
	youWinText.setFillColor(sf::Color::Yellow);
	youWinText.setString("You Win!");
	youWinText.setPosition(420, 470);

	sf::Text restartText;
	restartText.setFont(font);
	restartText.setCharacterSize(25);
	restartText.setFillColor(sf::Color::White);
	restartText.setString("Presiona R para reiniciar \nE para salir");
	restartText.setPosition(810, 960);


	//Bucle principal
	while (window.isOpen() && continuePlaying) {

		bool opening = PlaySound(TEXT("SuperMario2.wav"), NULL, SND_NOSTOP | SND_ASYNC);
		//PlaySound(TEXT("SMB2Overworld.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				continuePlaying = false;
			}
			else if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode == 's' || event.text.unicode == 'S') {
					decision = 's';
					peleaTriggered = true;
				}
				else if (event.text.unicode == 'n' || event.text.unicode == 'N') {
					decision = 'n';
					peleaTriggered = true;
				}
			}
		}


		sf::Time deltaTime = clock.restart();
		sf::Vector2f movement(0.f, 0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			movement.y += speed * deltaTime.asSeconds();
			rectSourceSprite.top = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			movement.x += speed * deltaTime.asSeconds();
			rectSourceSprite.top = 99;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			movement.x -= speed * deltaTime.asSeconds();
			rectSourceSprite.top = 208;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			movement.y -= speed * deltaTime.asSeconds();
			rectSourceSprite.top = 318;
		}

		// Animación de movimiento horizontal
		if (movement.x != 0.f) {
			if (rectSourceSprite.left >= 231)
				rectSourceSprite.left = 0;
			else
				rectSourceSprite.left += 80;
		}
		else if (movement.y != 0.f) {
			if (rectSourceSprite.left >= 240)
				rectSourceSprite.left = 0;
			else
				rectSourceSprite.left += 80;
		}
		else {
			rectSourceSprite.left = 0;
		}

		playerSprite.setTextureRect(rectSourceSprite);
		playerSprite.move(movement);

		//Area de juego
		sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
		if (playerBounds.left < 130)
			playerSprite.setPosition(130, playerBounds.top);
		if (playerBounds.top < 120)
			playerSprite.setPosition(playerSprite.getPosition().x, 120);
		if (playerBounds.left + playerBounds.width > boardWidth - 680)
			playerSprite.setPosition(boardWidth - playerBounds.width - 680, playerBounds.top);
		if (playerBounds.top + playerBounds.height > boardHeight - 465)
			playerSprite.setPosition(playerSprite.getPosition().x, boardHeight - playerBounds.height - 465);


		window.clear();
		window.draw(backgroundSprite);


		//Area 0 profe enemigo final
		if (isInArea(playerSprite, sf::Vector2f(activationArea0.left, activationArea0.top), sf::Vector2f(activationArea0.left + activationArea0.width, activationArea0.top + activationArea0.height))) {


			if (!peleaTriggered) {
				window.draw(profeExText);
				window.draw(listoExText);
			}

			if (peleaTriggered) {

				if (decision == 'n') {
					daniText.setString("-Aun no estoy listo!");
				}
				else if (decision == 's') {
					daniText.setString("-Vamos a ello");
					profe.setAttackEsp(true);
					PlaySound(TEXT("examenFinal.wav"), NULL, SND_ASYNC);

				}

				daniText.setPosition(760, 215);
				showResponse = true;
				responseTimer.restart();

				peleaTriggered = false;
			}

			if (showResponse) {
				window.draw(daniText);

				if (responseTimer.getElapsedTime().asSeconds() >= 2.0f) {
					showResponse = false;

				}
			}

		}


		//Area 1 pringao 1
		if (isInArea(playerSprite, sf::Vector2f(activationArea1.left, activationArea1.top), sf::Vector2f(activationArea1.left + activationArea1.width, activationArea1.top + activationArea1.height))) {
			if (!peleaTriggered) {
				window.draw(pringao1Text);
				window.draw(molestarText);
			}

			if (peleaTriggered) {

				if (decision == 'n') {
					daniText.setString(dani.getName() + "ignora a pringao!");
				}
				else if (decision == 's') {
					daniText.setString("-Calla retrasado");
					PlaySound(TEXT("bubble.wav"), NULL, SND_ASYNC);

					// colleja a retrasado
					dani.setAttack(true);
					daniText.setString(dani.getName() + "le da una colleja al retrasado!");
					srand(time(NULL));
					int randomValue = rand() % 2;
					profe.setAttack(randomValue);
					bool profesoraVe = profe.getAttack();
					if (profesoraVe) {
						castigado = true;
						if (castigado) {

							profeText.setString(profe.getName() + dani.getName() + "Castigado!");
							PlaySound(TEXT("newSuperMarioBrosStomp.wav"), NULL, SND_ASYNC);
							profeText.setPosition(770, 225);
							showCastigo = true;
							castigoTimer.restart();
							castigado = false;
							dani.setLife(dani.getLife() - 1);
							if (dani.getLife() == 2) {
								showHeart3 = false;
							}
							if (dani.getLife() == 1) {
								showHeart2 = false;
							}
							if (dani.getLife() == 0) {
								showHeart1 = false;
								gameOver = true;
								PlaySound(TEXT("gameover.wav"), NULL, SND_ASYNC);
							}
						}
					}
				}

				daniText.setPosition(770, 180);
				showResponse = true;
				responseTimer.restart();

				peleaTriggered = false;
			}
			if (showCastigo) {
				window.draw(profeText);

				if (castigoTimer.getElapsedTime().asSeconds() >= 3.0f) {
					showCastigo = false;
					playerSprite.setPosition(634, 210);
				}
			}
			if (showResponse) {
				window.draw(daniText);

				if (responseTimer.getElapsedTime().asSeconds() >= 3.0f) {
					showResponse = false;

				}
			}

		}

		//Area 2 puerta salida
		if (isInArea(playerSprite, sf::Vector2f(activationArea2.left, activationArea2.top), sf::Vector2f(activationArea2.left + activationArea2.width, activationArea2.top + activationArea2.height))) {
			if (!peleaTriggered) {
				window.draw(salidaText);
			}

			if (peleaTriggered) {
				if (decision == 'n') {
					//are2Text.setString("No!");
					firstTextDisplayed = true; // Mostrar primer texto
					secondTextDisplayed = false; // Ocultar segundo texto
				}
				else if (decision == 's') {
					are2Text.setString("Si!");
					PlaySound(TEXT("hey-childish-chant.wav"), NULL, SND_ASYNC);
					profeText.setString(profe.getName() + dani.getName() + "espera... \nNecesito que vengas antes de irte.");
					firstTextDisplayed = false; // Ocultar primer texto
					secondTextDisplayed = true; // Mostrar segundo texto
				}

				//are2Text.setPosition(770, 130);
				profeText.setPosition(770, 130);
				showResponse = true;
				responseTimer.restart();

				peleaTriggered = false;
			}

			if (showResponse) {
				if (firstTextDisplayed) {
					window.draw(are2Text);
				}
				if (secondTextDisplayed) {
					//window.draw(are2Text);
					window.draw(profeText);
				}

				if (responseTimer.getElapsedTime().asSeconds() >= 4.0f) {
					showResponse = false;
				}
			}

		}

		//Area 3 pringao 2
		if (isInArea(playerSprite, sf::Vector2f(activationArea3.left, activationArea3.top), sf::Vector2f(activationArea3.left + activationArea3.width, activationArea3.top + activationArea3.height))) {
			if (!peleaTriggered) {

				window.draw(pringao2Text);

				window.draw(molestarText);
			}
			if (peleaTriggered) {
				if (decision == 'n') {
					daniText.setString(dani.getName() + "ignora a pringao!");
				}
				else if (decision == 's') {
					daniText.setString("-Calla retrasado");
					PlaySound(TEXT("bubble.wav"), NULL, SND_ASYNC);

					// colleja a retrasado
					dani.setAttack(true);
					daniText.setString(dani.getName() + "le da una colleja al retrasado!");
					srand(time(NULL));
					int randomValue = rand() % 2;
					profe.setAttack(randomValue);
					bool profesoraVe = profe.getAttack();
					if (profesoraVe) {
						castigado = true;
						if (castigado) {

							profeText.setString(profe.getName() + dani.getName() + "Castigado!");
							PlaySound(TEXT("newSuperMarioBrosStomp.wav"), NULL, SND_ASYNC);
							profeText.setPosition(770, 225);
							showCastigo = true;
							castigoTimer.restart();
							castigado = false;
							dani.setLife(dani.getLife() - 1);
							if (dani.getLife() == 2) {
								showHeart3 = false;
							}
							if (dani.getLife() == 1) {
								showHeart2 = false;
							}
							if (dani.getLife() == 0) {
								showHeart1 = false;
								gameOver = true;
								PlaySound(TEXT("gameover.wav"), NULL, SND_ASYNC);
							}
						}
					}
				}

				daniText.setPosition(770, 180);
				showResponse = true;
				responseTimer.restart();

				peleaTriggered = false;
			}
			if (showCastigo) {
				window.draw(profeText);

				if (castigoTimer.getElapsedTime().asSeconds() >= 3.0f) {
					showCastigo = false;
					playerSprite.setPosition(634, 225);
				}
			}
			if (showResponse) {
				window.draw(daniText);

				if (responseTimer.getElapsedTime().asSeconds() >= 3.0f) {
					showResponse = false;

				}
			}

		}


		//corazones
		if (showHeart1) {
			window.draw(corazonSprite1);
		}
		if (showHeart2) {
			window.draw(corazonSprite2);
		}
		if (showHeart3) {
			window.draw(corazonSprite3);
		}

		window.draw(playerSprite);
		window.draw(text);


		//examen del enemigo final
		if (profe.getAttackEsp()) {
			PlaySound(TEXT("Pokemon1.wav"), NULL, SND_NOSTOP | SND_ASYNC);
			PlaySound(TEXT("Pokemon2.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);
			window.draw(examenSprite);
			window.draw(tituloExText);

			if (preguntaActual == 1)
			{
				preguntaExText.setString(L"Java es un lenguaje de programación \nde código abierto?");
				respuestaExText.setString("Verdadero o Falso (v/f)");
				window.draw(preguntaExText);
				window.draw(respuestaExText);
				preguntaExText.setPosition(420, 385);
				respuestaExText.setPosition(530, 485);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) || sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				{

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
					{
						examen++;
					}

					preguntaActual++;
				}
			}
			else if (preguntaActual == 2)
			{
				preguntaExText.setString("La sentencia int[] numbers = {1, 2, 3}; \nEs correcta?");
				respuestaExText.setString("Verdadero o Falso (v/f)");
				window.draw(preguntaExText);
				window.draw(respuestaExText);
				preguntaExText.setPosition(420, 385);
				respuestaExText.setPosition(530, 485);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) || sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				{

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
					{
						examen++;
					}

					preguntaActual++;
				}
			}
			else if (preguntaActual == 3)
			{
				preguntaExText.setString("Java es un lenguaje de programación \npuramente orientado a objetos?");
				respuestaExText.setString("Verdadero o Falso (v/f)");
				window.draw(preguntaExText);
				window.draw(respuestaExText);
				preguntaExText.setPosition(420, 385);
				respuestaExText.setPosition(530, 485);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) || sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				{

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
					{
						examen++;
					}

					preguntaActual++;
				}
			}
			else if (preguntaActual == 4)
			{
				preguntaExText.setString("El operador == en Java compara el \ncontenido de dos objetos?");
				respuestaExText.setString("Verdadero o Falso (v/f)");
				window.draw(preguntaExText);
				window.draw(respuestaExText);
				preguntaExText.setPosition(420, 385);
				respuestaExText.setPosition(530, 485);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) || sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				{

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
					{
						examen++;
					}

					preguntaActual++;
				}
			}
			else if (preguntaActual == 5)
			{
				preguntaExText.setString("La sentencia switch en Java permite \ntomar decisiones basadas en múltiples \ncondiciones?");
				respuestaExText.setString("Verdadero o Falso (v/f)");
				window.draw(preguntaExText);
				window.draw(respuestaExText);
				preguntaExText.setPosition(420, 385);
				respuestaExText.setPosition(530, 535);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) || sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
					{
						examen++;
					}
					preguntaActual++;
				}
			}
			else if (preguntaActual == 6)
			{
				preguntaExText.setString("El examen ha finalizado \nPulsa la tecla 'C' para continuar");
				window.draw(preguntaExText);
				preguntaExText.setPosition(420, 385);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
				{
					if (examen < 3)
					{
						PlaySound(TEXT("gameover.wav"), NULL, SND_ASYNC);
						profeText.setString("Suspendido!  a recuperacion!");
						profeText.setPosition(450, 395);
						profe.setAttackEsp(false);
						showHeart1 = false;
						showHeart2 = false;
						showHeart3 = false;
						gameOver = true;

						respuestaTimer.restart();
					}
					else
					{
						examenAprobado = true;

						youWin = true;
						PlaySound(TEXT("winning.wav"), NULL, SND_ASYNC);
						if (examenAprobado)
						{
							profeText.setString("Has aprobado el examen!\nFelicidades.");
							profeText.setPosition(450, 390);

							resultadoExamen = true;
						}

						respuestaTimer.restart();
					}

					preguntaActual++;
				}
			}

			//temporisador de texto
			if (resultadoExamen)
			{
				window.draw(profeText);
				window.draw(restartText);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
					{
						// Reiniciar el juego
						gameOver = false;
						youWin = false;
						dani.setLife(3);
						showHeart1 = true;
						showHeart2 = true;
						showHeart3 = true;
						examen = 0;
						preguntaActual = 1;
						playerSprite.setPosition(634, 225);
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					{
						exit(0);
					}
				}

				if (respuestaTimer.getElapsedTime().asSeconds() >= 3.0f)
				{
					resultadoExamen = false;

					profe.setAttackEsp(false);
				}
			}

			//resultado
			string valorExTexto = to_string(examen * 2);

			resultadoExText.setString("El resultado es un: " + valorExTexto);
			window.draw(resultadoExText);
			resultadoExText.setPosition(560, 635);

		}

		//GameOver y restart
		if (gameOver) {
			PlaySound(TEXT("SMB2Overworld.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);
			window.draw(gameOverText);
			window.draw(restartText);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					PlaySound(TEXT("SMB2Overworld.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);
					// Reiniciar el juego
					gameOver = false;
					youWin = false;
					dani.setLife(3);
					showHeart1 = true;
					showHeart2 = true;
					showHeart3 = true;
					examen = 0;
					preguntaActual = 1;
					playerSprite.setPosition(634, 215);

				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					exit(0);
				}
			}
		}
		//You Win y restart
		if (youWin) {

			showHeart1 = false;
			showHeart2 = false;
			showHeart3 = false;
			window.draw(youWinText);
			window.draw(restartText);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					// Reiniciar el juego
					gameOver = false;
					youWin = false;
					dani.setLife(3);
					showHeart1 = true;
					showHeart2 = true;
					showHeart3 = true;
					examen = 0;
					preguntaActual = 1;
					playerSprite.setPosition(634, 215);
					PlaySound(TEXT("SMB2Overworld.wav"), NULL, SND_LOOP | SND_NOSTOP | SND_ASYNC);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					exit(0);
				}
			}
		}

		window.display();
	}
	return 0;
}


int main() {

	DaniBoy dani("Dani, ", 3, 1);
	DaniBoy pardillo("Pardillo", 1, 0);
	EnemigoFinal profe("Ms. Carmen: ", 1, false, false);
	portada();
	grafico(dani, profe);

	return 0;
}
