#include "Entity.hpp"

Entity::Entity()
{

}

Entity::~Entity()
{
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

void Entity::update()
{
	if (moved)
		syncSprite();
}
