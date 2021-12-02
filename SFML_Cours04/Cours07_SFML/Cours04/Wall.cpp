#include "Wall.hpp"

Wall::Wall(float _cx, float _cy, int _stride)
{
	sf::RectangleShape* _spr = new sf::RectangleShape(sf::Vector2f(0, 0));
	*_spr = SetRectangleWOutline(sf::Vector2f(12, 28), sf::Color::Blue, sf::Vector2f(_cx, _cy), sf::Color::Green, 1);
	_spr->setOrigin(_spr->getSize().x * 0.5f, _spr->getSize().y);

	this->spr = _spr;
	cx = _cx;
	cy = _cy;
	stride = _stride;
	syncSprite();
}

Wall::~Wall()
{
}
