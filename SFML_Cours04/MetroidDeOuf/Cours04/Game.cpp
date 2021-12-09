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
	this->player = new Player("Samus", 15, 1, 5, 5,5, stride);
	this->player->setWorld(world);
	this->player->setGravity(gravity);
}

void Game::initWorld()
{
	this->world = new World();
	world->gravity = this->gravity;
	int floor = 24;
	for (int i = 0; i < 20; i++)
		this->world->placeWall(i, floor);

}

void Game::initGrid()
{
	gridRct = sf::RectangleShape(sf::Vector2f(stride, stride));
	gridRct.setOutlineColor(sf::Color::White);
	gridRct.setOutlineThickness(0.9f);
	gridRct.setFillColor(sf::Color::Transparent);
	gridRct.setOrigin(stride / 2, stride / 2);
}

#pragma endregion

Game::Game()
{
	this->initWindow();
	this->initWorld();
	this->initPlayer();
	this->initMusic();
	this->initGrid();

	mouseShape = SetCircle(3, sf::Color::Magenta, vectoriToVectorf(sf::Mouse::getPosition(window)));
	mouseShape.setOrigin(mouseShape.getRadius(), mouseShape.getRadius());

	//tmp
	sf::err().rdbuf(NULL);
}

Game::~Game()
{
}

void Game::update()
{
	mouseShape.setPosition(vectoriToVectorf(sf::Mouse::getPosition(window)));
	//dt
	elapsedTime = clock.getElapsedTime();
	dt = elapsedTime.asSeconds();
	clock.restart();

	//updates
	player->update(dt);

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
				break;

			case sf::Event::MouseButtonPressed:
				checkPressedMouse(gameEvent.key.code);
				break;

		}
	}

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

		default:
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

void Game::checkPressedMouse(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Mouse::Left:
			if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				world->placeWall(mousePosition.x / stride, mousePosition.y / stride);
			}
		break;
	}
}

void Game::processImGui()
{
	bool toolActive;
	ImGui::SFML::Update(window, elapsedTime);

	ImGui::Begin("Tools", &toolActive, ImGuiWindowFlags_MenuBar);
	ImGui::Checkbox("Debug mouse", &debugMouse);
	if (debugMouse)
	{
		ImGui::Text("Mouse : { x%d y%d }", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		float rad = mouseShape.getRadius();
		if (ImGui::SliderFloat("Shape size", &rad, 1, 10))
			mouseShape.setRadius(rad);
	}
	if (ImGui::DragFloat("Gravity", &gravity, 0.05f, -5, 5))
	{
		world->gravity = this->gravity;
	}
	
	float vol = audioManager.musicVolume;
	if (ImGui::DragFloat("Volume", &vol, 1, 0, 100))
	{
		audioManager.changeMusicVolume(vol);

	}
	ImGui::Checkbox("Draw grid", &renderGrid);
	if (renderGrid)
	{
		ImGui::DragFloat("Grid X", &gridSize.x, 1, 0); 
		ImGui::DragFloat("Grid Y", &gridSize.y, 1, 0);
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

void Game::drawGrid()
{
	for (int y = 0; y < gridSize.y * stride; y += stride) 
	{
		for (int x = 0; x < gridSize.x * stride; x += stride) 
		{
			gridRct.setPosition(x + stride, y + stride);
			window.draw(gridRct);
		}
	}
}

void Game::render()
{
	this->window.clear();

	if (debugMouse)
		window.draw(mouseShape);

	this->world->render(this->window);
	this->player->render(this->window);

	if (renderGrid)
		drawGrid();

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
