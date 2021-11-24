#pragma once

#include "SFML/Graphics.hpp"
#include "Utility.hpp"
#include "Shape.hpp"

class Pen
{
private:

	sf::CircleShape pencil;

	sf::RenderTexture* drawableSpace = nullptr;

	bool renderPen = true;

public:

	Pen(sf::Vector2f pos);
	~Pen();

	void enablePen(bool enabled);
	void changePencilColor(sf::Color _color);

	const sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void update(float dt);

	void render(sf::RenderTarget& target);

};