#pragma once
#include "Entity.hpp"
class Player : public Entity
{
private:

	//vars

	sf::CircleShape* c;

	//funcs

public:

	//vars


	//funcs

	Player(std::string _name, float _speed, float _invicibilityCD, float _maxHealth);
	~Player();

	void render(sf::RenderTarget& target);

};

