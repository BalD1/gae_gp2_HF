#include <iostream>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Shape.hpp"
#include "Utility.hpp"
#include "Entity.hpp"
#include "Turtle.hpp"
#include "CommandList.hpp"
#include "FileWatcher.hpp"

#pragma region Variables

sf::Vector2f GV_windowCenter;
sf::Vector2f GV_windowSize;
sf::Vector2i GV_mousePos;

Turtle* GV_turtle;

FileWatcher* GV_turtleCommandsFile;

bool gameEnd;
bool enterWasPressed = false;

#pragma endregion

void ProcessInputs(sf::RenderWindow& window, float dt);

int main()
{
#pragma region Set window

	sf::RenderWindow window(sf::VideoMode(1280, 720, 64), "wesh la mif c'est moi la fenetre de ouf");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

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

#pragma region ImGui variables

	bool moveForward = true;
	bool turnRight = true;
	bool penUp = false;

	float advanceTime = 1;
	float turnTime = 1;

	float advanceSpeed = GV_turtle->getBaseSpeed();
	float turnSpeed = GV_turtle->getBaseRotationSpeed();

#pragma endregion

	FileWatcher turtleCommandsFile("Assets/test.txt");
	GV_turtleCommandsFile = &turtleCommandsFile;

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
	float turtlePenColor[3] = { (float)255 / 255,(float)255 / 255,(float)255 / 255 };

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time elapsed = clock.getElapsedTime();
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				GV_turtle->saveCommandsInFile("Assets/commands.txt");
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					GV_turtle->saveCommandsInFile("Assets/commands.txt");
					window.close();
				}
			}
		}
#pragma region IMGUI

		ImGui::SFML::Update(window, clock.restart());
		bool toolActive;
		ImGui::Begin("Cc jsuis la fenetre", &toolActive, ImGuiWindowFlags_MenuBar);
		ImGui::Text("Mouse : { x%d y%d }", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		if (ImGui::Button("Advance", ImVec2(200, 20)))
		{
			if (!moveForward)
				advanceTime *= -1;
			GV_turtle->appendCommand(CommandList::CommandType::Advance, advanceTime);

			if (!moveForward)
				advanceTime *= -1;
		}
		ImGui::Spacing();

		if (ImGui::Button("Turn", ImVec2(200, 20)))
		{
			if (!turnRight)
				turnTime *= -1;

			GV_turtle->appendCommand(CommandList::CommandType::Turn, turnTime);

			if (!turnRight)
				turnTime *= -1;
		}
		ImGui::Spacing();

		if (ImGui::Button("Reset", ImVec2(200, 20)))
		{
			GV_turtle->reset();
		}
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Stats"))
			{
				if (ImGui::ColorEdit3("Pen color", turtlePenColor))
				{
					sf::Color c
					(
						(int)(turtlePenColor[0] * 255),
						(int)(turtlePenColor[1] * 255),
						(int)(turtlePenColor[2] * 255)
					);
					GV_turtle->changePencilColor(c);
				}
				if (ImGui::Checkbox("Pen up", &penUp))
				{
					if (penUp)
						GV_turtle->appendCommand(CommandList::CommandType::PenUp, 1);
					else
						GV_turtle->appendCommand(CommandList::CommandType::PenDown, 1);
				}
				ImGui::Spacing();

				ImGui::Checkbox("Forward", &moveForward);
				if (ImGui::SliderFloat("Advance speed", &advanceSpeed, 0, 300))
					GV_turtle->changeBaseSpeed(advanceSpeed);
				ImGui::SliderFloat("Advance Time", &advanceTime, 0, 10);
				ImGui::Spacing();

				ImGui::Checkbox("Turn right", &turnRight);
				if (ImGui::SliderFloat("Turn speed", &turnSpeed, 0, 360))
					GV_turtle->changeBaseRotationSpeed(turnSpeed);
				ImGui::SliderFloat("Turn Time", &turnTime, 0, 10);

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();

#pragma endregion

		if (!gameEnd)
		{
			GV_mousePos = sf::Mouse::getPosition(window);
			ProcessInputs(window, dt);
		}

		//========= Updates

		dt = elapsed.asSeconds();

		GV_turtle->update(dt);
		if (turtleCommandsFile.checkFileModification(dt))
		{
			GV_turtle->reset();
			GV_turtleCommandsFile->appendCommandsFromFile(GV_turtle);
		}

		//=========	Draws

		window.clear();

		window.draw(turtle);
		ImGui::SFML::Render(window);

		window.display();
	}

}

void ProcessInputs(sf::RenderWindow& window, float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && !enterWasPressed)
	{
		enterWasPressed = true;
		GV_turtleCommandsFile->appendCommandsFromFile(GV_turtle);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		GV_turtle->move(sf::Vector2f(1, 0), dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		GV_turtle->move(sf::Vector2f(-1, 0), dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		GV_turtle->rotate(1, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		GV_turtle->rotate(-1, dt);

	enterWasPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}