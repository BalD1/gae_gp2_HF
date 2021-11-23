#include <iostream>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Shape.hpp"
#include "Utility.hpp"
#include "Entity.hpp"
#include "Turtle.hpp"
#include "CommandList.hpp"

#pragma region Variables

sf::Vector2f GV_windowCenter;
sf::Vector2f GV_windowSize;
sf::Vector2i GV_mousePos;

Turtle* GV_turtle;

bool gameEnd;
bool enterWasPressed = false;

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

	CommandList* cmd1 = new CommandList(CommandList::CommandType::Advance, 1, 50);
	int minRan = -4;
	int maxRan = minRan * -1;

	/*
	for (int i = 1; i < 101; i++)
	{
		srand(i * 200);
		CommandList::Command* adv = cmd1->CreateCommand(CommandList::Advance, rand() %(maxRan - minRan) + minRan);
		CommandList::Command* trn = cmd1->CreateCommand(CommandList::Turn, rand() % (maxRan - minRan) + minRan);
		if (i % 2 == 0)
			GV_turtle->appendCommand(CommandList::CommandType::PenDown, 1);
		else
			GV_turtle->appendCommand(CommandList::CommandType::PenUp, 1);

		if (i % 5 == 0)
			GV_turtle->changePencilColor(sf::Color::Red);
		if (i % 7 == 0)
			GV_turtle->changePencilColor(sf::Color::Green);
		if (i % 8 == 0)
			GV_turtle->changePencilColor(sf::Color::White);

		GV_turtle->appendCommand(adv);
		GV_turtle->appendCommand(trn);
	}
	*/


	/*
	err = fopen_s(&fp, "Assets/test.txt", "w");
	if (err == 0)
	{
		printf("The file  was opened\n");
	}
	else
	{
		printf("The file was not opened\n");
	}
	if (fp != NULL)
	{
		fprintf(fp, "bonjour");
		fclose(fp);
	}
	*/

#pragma endregion

	gameEnd = false;

	sf::Music music;
	if (!music.openFromFile("Assets/Sounds/music.ogg"))
	{
		std::cout << "Could not load main music";
		return 0;
	}
	music.setVolume(0);
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
			if (event.type == sf::Event::KeyPressed)
			{
				/*
				if (event.key.code == sf::Keyboard::Z)
					GV_turtle->appendCommand(CommandList::CommandType::Advance, 1);

				if (event.key.code == sf::Keyboard::S)
					GV_turtle->appendCommand(CommandList::CommandType::Advance, -1);

				if (event.key.code == sf::Keyboard::D)
					GV_turtle->appendCommand(CommandList::CommandType::Turn, 1);

				if (event.key.code == sf::Keyboard::Q)
					GV_turtle->appendCommand(CommandList::CommandType::Turn, -1);

					*/
			}

		}

		if (!gameEnd)
		{
			GV_mousePos = sf::Mouse::getPosition(window);
			ProcessInputs(window, dt);
		}


		//========= Updates

		dt = elapsed.asSeconds();

		GV_turtle->update(dt);

		//=========	Draws

		window.clear();

		window.draw(turtle);

		window.display();
	}

}

void ProcessInputs(sf::RenderWindow& window, float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && !enterWasPressed)
	{
		enterWasPressed = true;

		FILE* fp;
		errno_t err;

		err = fopen_s(&fp, "Assets/test.txt", "rb");
		if (err == 0)
			printf("The file  was opened\n");
		else
			printf("The file was not opened\n");


		if (fp != NULL && !feof(fp))
		{
			char line[256] = {};
			while (true)
			{
				int64_t nb = 0;
				int64_t spd = 0;
				fscanf_s(fp, "%s %lld %lld\n", line, 256, &nb, &spd);
				std::string s = line;
				if (s == "Advance")
					GV_turtle->appendCommand(CommandList::CommandType::Advance, nb, spd);
				else if (s == "Turn")
					GV_turtle->appendCommand(CommandList::CommandType::Turn, nb, spd);
				else if (s == "PenUp")
					GV_turtle->appendCommand(CommandList::CommandType::PenUp, nb, spd);
				else if (s == "PenDown")
					GV_turtle->appendCommand(CommandList::CommandType::PenDown, nb, spd);

				if (feof(fp))
					break;
			}

		}
		GV_turtle->printCommandList();
		std::cout << enterWasPressed;
		fclose(fp);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		GV_turtle->move(sf::Vector2f(1, 0), dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		GV_turtle->move(sf::Vector2f(-1, 0), dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		GV_turtle->rotate(1, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		GV_turtle->rotate(-1, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		GV_turtle->appendCommand(CommandList::CommandType::PenUp, 1, 1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		GV_turtle->appendCommand(CommandList::CommandType::PenDown, 1, 1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		GV_turtle->changePencilColor(sf::Color::Red);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		GV_turtle->changePencilColor(sf::Color::Green);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
		GV_turtle->changePencilColor(sf::Color::Blue);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
		GV_turtle->changePencilColor(sf::Color::White);

		enterWasPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}