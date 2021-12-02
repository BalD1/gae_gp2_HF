#pragma once
#include "stdafx.hpp"
#include "Player.hpp"

class Game
{
private:

	// vars

	sf::RenderWindow window;
	sf::Event gameEvent;

	sf::Clock clock;
	sf::Time elapsedTime;
	float dt = 0;

	Player* player;

	// funcs

	void initWindow();
	void closeWindow();

	void initPlayer();

public:

	// vars

	sf::Vector2f windowSize;
	sf::Vector2f windowCenter;


	// funcs

	Game();
	~Game();


	void update();
	void checkPressedKey(sf::Keyboard::Key key);

	void processImGui();

	void render();

	float deltaTime();


	 sf::RenderWindow& getWindow() ;
};

