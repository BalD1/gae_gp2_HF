#pragma once
#include "Entity.hpp"
class Player : public Entity
{
private:

	//vars


	//funcs

public:

	//vars


	//funcs

	Player(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride);
	~Player();

	void im();

	void render(sf::RenderTarget& target);

};

