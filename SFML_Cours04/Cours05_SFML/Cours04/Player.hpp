#pragma once

#include "Entity.hpp"

class Entity;

class Player : public Entity
{
public:

#pragma region Funcs

	Player(sf::Texture& _texture, sf::Vector2f pos);
	Player(sf::Texture& _texture, float posX, float posY);
	~Player();

	void update(const float& dt);

	void render(sf::RenderTarget& target, const bool showHitbox);

#pragma endregion

private:

};