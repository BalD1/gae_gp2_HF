#pragma once
#include "Character.hpp"
class Enemy : public Character
{
private:

public:

	Enemy(std::string _name, float _cx, float _cy, int _stride, sf::Texture& _texture);
	~Enemy();
};

