#include "stdafx.hpp"
#include "Game.hpp"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "MetroidDeOuf", sf::Style::Close | sf::Style::Titlebar);
}

void Game::closeWindow()
{
	this->window.close();
}

Game::Game()
{
	this->initWindow();
}

Game::~Game()
{
}

void Game::update()
{
	//events
	while (this->window.pollEvent(this->gameEvent))
	{
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
}

void Game::checkPressedKey(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Escape:
			closeWindow();
			break;
	}
}

void Game::render()
{
	this->window.clear();

	this->window.display();
}


sf::RenderWindow& Game::getWindow()
{
	return this->window;
}
