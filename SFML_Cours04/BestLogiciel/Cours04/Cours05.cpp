#include <iostream>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Shape.hpp"
#include "Utility.hpp"
#include "Pen.hpp"

#pragma region Variables

sf::Vector2f GV_windowCenter;
sf::Vector2f GV_windowSize;
sf::Vector2i GV_mousePos;

Pen* GV_currentPen;

bool gameEnd;

#pragma endregion

void ProcessInputs(sf::RenderWindow& window, float dt);

int main()
{
#pragma region Set window

	sf::RenderWindow window(sf::VideoMode(1280, 720, 64), "wesh la mif c'est moi la fenetre de ouf");
	ImGui::SFML::Init(window);

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	GV_windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	GV_windowCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

	float dt = 0;

#pragma endregion

	Pen* p = new Pen(GV_windowCenter);
	GV_currentPen = p;

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
	float pencilColor[3] = { (float)255 / 255,(float)255 / 255,(float)255 / 255 };

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
				window.close();
		}
#pragma region IMGUI

		ImGui::SFML::Update(window, clock.restart());
		bool toolActive;
		ImGui::Begin("Cc jsuis la fenetre", &toolActive, ImGuiWindowFlags_MenuBar);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Tools"))
			{
				if (ImGui::ColorEdit3("Pen color", pencilColor))
				{
					sf::Color c
					(
						(int)(pencilColor[0] * 255),
						(int)(pencilColor[1] * 255),
						(int)(pencilColor[2] * 255)
					);
					GV_currentPen->changePencilColor(c);
				}

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

		//=========	Draws

		window.clear();

		GV_currentPen->render(window);
		ImGui::SFML::Render(window);

		window.display();
	}

}

void ProcessInputs(sf::RenderWindow& window, float dt)
{
}