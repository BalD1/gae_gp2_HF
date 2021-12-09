#pragma once
#include "stdafx.hpp"
#include "AudioManager.hpp"
#include "Player.hpp"
#include "World.hpp"

class Game
{
private:

	// vars

	sf::RenderWindow window;
	sf::Event gameEvent;

	sf::RectangleShape gridRct;
	sf::Vector2f gridSize = { 25,25 };
	bool renderGrid = false;

	bool debugMouse = false;

	sf::CircleShape mouseShape;

	sf::Clock clock;
	sf::Time elapsedTime;
	float dt = 0;

	AudioManager audioManager;

	Player* player;

	World* world;
	Entity* walls[20][20];

	// funcs

	void initWindow();
	void closeWindow();
	void initMusic();
	void initPlayer();
	void initWorld();
	void initGrid();

public:

	// vars

	sf::Vector2f			windowSize;
	sf::Vector2f			windowCenter;

	int						stride = 32;

	const float				gravity = 0.7f;

	// funcs

	Game();
	~Game();


	void update();
	void checkPressedKey(sf::Keyboard::Key key);
	void checkReleasedKey(sf::Keyboard::Key key);
	void checkPressedMouse(sf::Keyboard::Key key);

	void processImGui();

	void drawGrid();
	void render();

	float deltaTime();

	World* getWorld();
	sf::RenderWindow& getWindow();
};

