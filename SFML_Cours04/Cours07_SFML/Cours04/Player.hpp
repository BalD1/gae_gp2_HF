#pragma once
#include "Entity.hpp"

class Player : public Entity
{
private:


public:

	Player(float _cx, float _cy, int _stride);
	~Player();

	void im();

	void render(sf::RenderTarget& target);
};

