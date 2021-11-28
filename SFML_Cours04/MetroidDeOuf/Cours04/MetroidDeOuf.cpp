#include <iostream>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Shape.hpp"
#include "Utility.hpp"
#include "Entity.hpp"
#include "FileWatcher.hpp"

#pragma region Variables

sf::Vector2f GV_windowCenter;
sf::Vector2f GV_windowSize;
sf::Vector2i GV_mousePos;

bool gameEnd = false;
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

#pragma region ImGui variables

#pragma endregion

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
#pragma region IMGUI

		ImGui::SFML::Update(window, clock.restart());
		bool toolActive;
		ImGui::Begin("Cc jsuis la fenetre", &toolActive, ImGuiWindowFlags_MenuBar);
		ImGui::Text("Mouse : { x%d y%d }", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::Button("Save"))
				{

				}
				ImGui::Spacing();
				if (ImGui::Button("Load"))
				{

				}
				ImGui::Spacing();

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

		ImGui::SFML::Render(window);

		window.display();
	}

}

void ProcessInputs(sf::RenderWindow& window, float dt)
{

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))

	enterWasPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}