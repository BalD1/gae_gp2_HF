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

	std::vector<sf::VertexArray> vertices;
	vertices.push_back(sf::VertexArray());
	vertices[0].setPrimitiveType(sf::LinesStrip);
	int lines_number = 0;
	bool isMousePressed = false;

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
	sf::Vector2f Border_Offset(-5, -25); // Compensate for the Window frame when calling window.getPosition()

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
			if (event.type == sf::Event::MouseButtonPressed)
			{
				switch (event.key.code)
				{
					case sf::Mouse::Left:
							isMousePressed = true;
						if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
						{
							GV_currentPen->enablePen(true);
						}
						break;

					default:
						break;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				switch (event.key.code)
				{
					case sf::Mouse::Left:
						lines_number++;
						vertices.push_back(sf::VertexArray());
						vertices[lines_number].setPrimitiveType(sf::LinesStrip);
						isMousePressed = false;
						GV_currentPen->enablePen(false);
						break;

					default:
						break;
				}
			}
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

		GV_currentPen->setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		//=========	Draws
		if (isMousePressed) // See "locked" definition
		{
				//.append(Position, Color) : .append(MousePos - WindowPos + MouseOffset, curr_col)
				//vertices[lines_number].append(sf::Vertex(sf::Vector2f(sf::Mouse::getPosition().x - window.getPosition().x + Border_Offset.x, sf::Mouse::getPosition().y - window.getPosition().y + Border_Offset.y), sf::Color::White));

			
		}

		window.clear();

		for (int i = 0; i < vertices.size(); i++)
		{
			window.draw(vertices[i]);
		}

		GV_currentPen->render(window);
		ImGui::SFML::Render(window);

		window.display();
	}

}

void ProcessInputs(sf::RenderWindow& window, float dt)
{
}