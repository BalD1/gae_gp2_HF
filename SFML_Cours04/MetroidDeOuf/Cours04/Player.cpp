#include "stdafx.hpp"
#include "Player.hpp"

Player::Player(
	std::string _name, 
	float _speed, 
	float _invicibilityCD, 
	float _maxHealth) 
	: 
	Entity(_name, 
		_speed, 
		_invicibilityCD, 
		_maxHealth)
{
	c = new sf::CircleShape();
	*c = SetCircle(10, sf::Color::Red, Vector2zero());
}

Player::~Player()
{
	delete(c);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(*this->c);
}
