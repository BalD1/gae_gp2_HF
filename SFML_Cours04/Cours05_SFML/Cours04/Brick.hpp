#pragma once

#include "Entity.hpp"

class Entity;

class Brick : public Entity
{
public:



	Brick(sf::Texture& _texture, sf::Vector2f pos);
	Brick(sf::Texture& _texture, float posX, float posY);
	~Brick();

	void update(float dt);

	void render(sf::RenderWindow& target, bool showHitbox);

};