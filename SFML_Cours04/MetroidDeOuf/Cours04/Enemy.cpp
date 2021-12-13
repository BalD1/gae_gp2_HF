#include "Enemy.hpp"

Enemy::Enemy(std::string _name, float _cx, float _cy, int _stride, sf::Texture& _texture)
	:Character(_name, _cx, _cy, _stride)
{
	this->texture = &_texture;
}

Enemy::~Enemy()
{
}
