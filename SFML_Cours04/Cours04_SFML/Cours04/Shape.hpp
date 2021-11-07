#pragma once

#include <SFML/Graphics.hpp>

sf::CircleShape SetCircle(int size, sf::Color color, sf::Vector2f pos)
{
	sf::CircleShape tmpC(size);
	tmpC.setFillColor(color);
	tmpC.setPosition(pos);

	return tmpC;
}

sf::RectangleShape SetRectangle(sf::Vector2f size, sf::Color color, sf::Vector2f pos)
{
	sf::RectangleShape tmpR(size);
	tmpR.setFillColor(color);
	tmpR.setPosition(pos);

	return tmpR;
}
sf::RectangleShape SetRectangle(float sizeX, float sizeY, sf::Color color, sf::Vector2f pos)
{
	sf::RectangleShape tmpR(sf::Vector2f(sizeX, sizeY));
	tmpR.setFillColor(color);
	tmpR.setPosition(pos);

	return tmpR;
}

sf::Text SetText(int size, std::string txt, sf::Color color, sf::Font font)
{
	sf::Text t;
	t.setCharacterSize(size);
	t.setString(txt);
	t.setFillColor(color);
	t.setFont(font);

	return t;
}