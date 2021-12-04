#include "stdafx.hpp"
#include "Entity.hpp"

void Entity::init()
{
	this->hitbox = nullptr;
	this->spr = nullptr;
}

Entity::Entity(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride)
{
	init();
	this->name = _name;
	this->speed = _speed;
	this->invincibility_CD = _invicibilityCD;
	this->currentHealth = maxHealth = _maxHealth;
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

void Entity::manageMovements()
{
	// x
	rx += dx;
	dx *= 0.96f;

	while (rx > 1) { rx--; cx++; }
	while (rx < 0) { rx++; cx--; }

	// y
	ry += dy;
	dy *= 0.96f;

	while (ry > 1) { ry--; cy++; }
	while (ry < 0) { ry++; cy--; }
}

void Entity::syncSprite()
{
	manageMovements();
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
	if (moved)
		syncSprite();
}