#include "Entity.hpp"

void Entity::init()
{
	this->spr = nullptr;
}

Entity::Entity(float _cx, float _cy, int _stride)
{
	init();
	this->cx = _cx;
	this->cy = _cy;
	this->stride = _stride;
}

Entity::~Entity()
{
}

void Entity::setTag(const std::string _tag)
{
	this->tag = _tag;
}

const std::string Entity::getTag()
{
	return this->tag;
}

void Entity::syncSprite(float dt)
{
	xx = std::int16_t((cx + rx) * stride);
	yy = std::int16_t((cy + ry) * stride);
	this->spr->setPosition(xx, yy);
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(*spr);
}

void Entity::update(float dt)
{

}