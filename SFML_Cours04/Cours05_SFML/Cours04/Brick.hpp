#pragma once

#include "Entity.hpp"
#include "Hitbox.hpp"

class Entity;

class Brick : public Entity
{
public:

	Brick(sf::Texture& _texture, sf::Vector2f pos);
	Brick(sf::Texture& _texture, float posX, float posY);

	Hitbox* verticalBox = nullptr;

	~Brick();

	void update(float dt);

	void render(sf::RenderWindow& target, bool showHitbox);

};