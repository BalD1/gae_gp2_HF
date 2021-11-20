#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Shape.hpp"
#include "Utility.hpp"
#include "Entity.hpp"
#include "Turtle.hpp"
#include "LinkedList.hpp"

#pragma region Variables

sf::Vector2f GV_windowCenter;
sf::Vector2f GV_windowSize;
sf::Vector2i GV_mousePos;

Turtle* GV_turtle;

bool gameEnd;

#pragma endregion

void ProcessInputs(sf::RenderWindow& window, float dt);

int main()
{
#pragma region Set window

	sf::RenderWindow window(sf::VideoMode(1280, 720, 64), "wesh la mif c'est moi la fenetre de ouf");

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	GV_windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	GV_windowCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

	float dt = 0;

#pragma endregion

#pragma region Turtle

	Turtle turtle = Turtle(GV_windowCenter);
	GV_turtle = &turtle;

#pragma endregion





	gameEnd = false;

	sf::Music music;
	if (!music.openFromFile("Assets/Sounds/music.ogg"))
	{
		std::cout << "Could not load main music";
		return 0;
	}
	music.setVolume(20);
	music.setLoop(true);
	music.play();

	sf::err().rdbuf(NULL);

	GV_mousePos = sf::Mouse::getPosition(window);

#pragma region Texts

	sf::Font cybrpnukFont;
	if (!cybrpnukFont.loadFromFile("Cybrpnuk2.ttf"));
	{

	}

#pragma endregion

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time elapsed = clock.getElapsedTime();
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		if (!gameEnd)
		{
			GV_mousePos = sf::Mouse::getPosition(window);
			ProcessInputs(window, dt);
		}

		dt = elapsed.asSeconds();

		window.clear();

		window.draw(turtle);

		window.display();
	}

}

void ProcessInputs(sf::RenderWindow& window, float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		GV_turtle->move(sf::Vector2f(5, 0), dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		GV_turtle->move(sf::Vector2f(-5, 0), dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		GV_turtle->rotate(1, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		GV_turtle->rotate(-1, dt);
}