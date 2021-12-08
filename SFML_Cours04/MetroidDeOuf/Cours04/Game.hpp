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

	sf::Clock clock;
	sf::Time elapsedTime;
	float dt = 0;

	AudioManager audioManager;

	Player* player;

	World* world;

	// funcs

	void initWindow();
	void closeWindow();
	void initMusic();
	void initPlayer();
	void initWorld();

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

	void processImGui();

	void render();

	float deltaTime();


	 sf::RenderWindow& getWindow() ;
};

