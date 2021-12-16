#pragma once
#include "Character.hpp"
class Enemy : public Character
{
private:

	int					direction = 1;

public:

	Enemy(std::string _name, float _cx, float _cy, int _stride, sf::Texture& _texture);
	~Enemy();

	void manageMovements(float dt);
	void update(float dt);
};

