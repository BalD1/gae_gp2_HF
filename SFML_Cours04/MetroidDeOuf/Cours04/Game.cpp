#include "stdafx.hpp"
#include "Game.hpp"

#pragma region Initiations

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1280, 960), "MetroidDeOuf", sf::Style::Close | sf::Style::Titlebar);
	ImGui::SFML::Init(this->window);

	windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	windowCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
}

void Game::closeWindow()
{
	this->window.close();
}

void Game::initMusic()
{
	audioManager.setMusic("Assets/Sounds/music.ogg");
}

void Game::initPlayer()
{
	this->player = new Player("Samus", 15, 1, 5, windowCenter.x / stride, windowCenter.y / stride, stride);
	this->player->setGravity(gravity);
}

void Game::initWorld()
{
	this->world = new World();
	for (int i = 0; i < 10; i++)
		this->world->placeWall(i, i);
}

#pragma endregion

Game::Game()
{
	this->initWindow();
	this->initWorld();
	this->initPlayer();
	this->initMusic();

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
			case sf::Event::KeyReleased:
				checkReleasedKey(this->gameEvent.key.code);

		}
	}


	//dt
	elapsedTime = clock.getElapsedTime();
	dt = elapsedTime.asSeconds();
	clock.restart();

	//updates
	player->update(dt);

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
		case sf::Keyboard::Space:
			player->manageEventInputs(key);
			break;
	}
}

void Game::checkReleasedKey(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Escape:
			closeWindow();
			break;
		case sf::Keyboard::Space:
			player->manageEventInputsRelease(key);
			break;
	}
}

void Game::processImGui()
{
	bool toolActive;
	ImGui::SFML::Update(window, elapsedTime);

	ImGui::Begin("Tools", &toolActive, ImGuiWindowFlags_MenuBar);
	ImGui::Text("Mouse : { x%d y%d }", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	ImGui::Value("Gravity : ", (float)gravity);
	float vol = audioManager.musicVolume;
	if (ImGui::DragFloat("Volume", &vol, 1, 0, 100))
	{
		audioManager.changeMusicVolume(vol);
	}


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

	this->world->render(this->window);
	this->player->render(this->window);

	ImGui::SFML::Render(window);

	this->window.display();
}

float Game::deltaTime()
{
	return this->dt;
}


World* Game::getWorld()
{
	return this->world;
}

sf::RenderWindow& Game::getWindow()
{
	return this->window;
}
