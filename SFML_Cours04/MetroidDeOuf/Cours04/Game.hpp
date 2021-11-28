#pragma once
#include "stdafx.hpp"
class Game
{
private:
	sf::RenderWindow window;
	sf::Event gameEvent;

	void initWindow();
	void closeWindow();

public:

	Game();
	~Game();


	void update();
	void checkPressedKey(sf::Keyboard::Key key);

	void render();


	 sf::RenderWindow& getWindow() ;
};

