#include <iostream>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Shape.hpp"
#include "Utility.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Wall.hpp"

#pragma region Variables

sf::Vector2f GV_windowCenter;
sf::Vector2f GV_windowSize;
sf::Vector2i GV_mousePos;

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

	int stride = 16;


	Player* player = new Player(GV_windowCenter.x / stride, GV_windowCenter.y / stride, stride);
	Wall* wall = new Wall(GV_windowCenter.x * 1.5 / stride, GV_windowCenter.y / stride, stride);

	gameEnd = false;

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time elapsed = clock.getElapsedTime();
		clock.restart();
		ImGui::SFML::Update(window, elapsed);

		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		if (!gameEnd)
		{
			GV_mousePos = sf::Mouse::getPosition(window);
			ProcessInputs(window, dt);
		}




		//========= Updates

		player->update();

		if (player->cx - 1 == wall->cx && player->rx >= 0.3f)
		{
			player->rx = 0.3f;
			player->dx = 0;
		}

		if (player->cx + 1 == wall->cx && player->rx >= 0.3f)
		{
			player->rx = 0.3f;
			player->dx = 0;
		}

		dt = elapsed.asSeconds();

#pragma region ImGui

		ImGui::Begin("Entities manager");
		ImGui::Text("Player");
		ImGui::Value("cx ", (int)player->cx);
		ImGui::SameLine();
		ImGui::Value(" cy ", (int)player->cy);
		ImGui::Value("rx ", (float)player->rx);
		ImGui::SameLine();
		ImGui::Value(" ry ", (float)player->ry);
		ImGui::Text("Wall");
		ImGui::Value("cx ", (int)wall->cx);
		ImGui::SameLine();
		ImGui::Value(" cy ", (int)wall->cy);		
		ImGui::Value("rx ", (float)wall->rx);
		ImGui::SameLine();
		ImGui::Value(" ry ", (float)wall->ry);
		ImGui::End();

#pragma endregion


		window.clear();

		player->render(window);
		wall->render(window);

		window.display();
	}

}

void ProcessInputs(sf::RenderWindow& window, float dt)
{

}