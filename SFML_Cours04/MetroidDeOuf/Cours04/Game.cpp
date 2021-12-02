#include "stdafx.hpp"
#include "Game.hpp"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "MetroidDeOuf", sf::Style::Close | sf::Style::Titlebar);
	ImGui::SFML::Init(this->window);

	windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	windowCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
}

void Game::closeWindow()
{
	this->window.close();
}

void Game::initPlayer()
{
	this->player = new Player("Samus", 5, 1, 5);
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();

	//tmp
	sf::err().rdbuf(NULL);
}

Game::~Game()
{
}

void Game::update()
{
	//events
	while (this->window.pollEvent(this->gameEvent))
	{
		ImGui::SFML::ProcessEvent(this->gameEvent);
		switch (gameEvent.type)
		{
			case sf::Event::Closed:
				closeWindow();
				break;
			case sf::Event::KeyPressed:
				checkPressedKey(this->gameEvent.key.code);
				break;

		}
	}


	//dt
	elapsedTime = clock.getElapsedTime();
	dt = elapsedTime.asSeconds();
	clock.restart();

	//ImGui
	this->processImGui();
}

void Game::checkPressedKey(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Escape:
			closeWindow();
			break;
		case sf::Keyboard::Q:
			break;
		case sf::Keyboard::D:
			break;
	}
}

void Game::processImGui()
{
	bool toolActive;
	ImGui::SFML::Update(window, elapsedTime);

	ImGui::Begin("Tools", &toolActive, ImGuiWindowFlags_MenuBar);
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
}

void Game::render()
{
	this->window.clear();

	this->player->render(this->window);

	ImGui::SFML::Render(window);

	this->window.display();
}

float Game::deltaTime()
{
	return this->dt;
}


sf::RenderWindow& Game::getWindow()
{
	return this->window;
}
