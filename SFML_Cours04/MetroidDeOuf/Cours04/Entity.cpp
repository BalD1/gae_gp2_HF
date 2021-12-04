#include "Entity.hpp"

void Entity::init()
{
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

void Entity::setGravity(float _gravity, bool _ignoreGravity)
{
	this->gravity = _gravity;
	this->ignoreGravity = _ignoreGravity;
}

void Entity::setTag(const std::string _tag)
{
	this->tag = _tag;
}

const std::string Entity::getTag()
{
	return this->tag;
}

void Entity::manageMovements(float dt)
{
	// x

	rx += dx * dt;
	dx *= 0.96f;
	if (cx - 1 < 0 && rx <= 0.1f)
	{
		rx = 0.1f;
		dx = 0;
	}
	if (cx + 1 > 36 && rx >= 0.7f)
	{
		rx = 0.7f;
		dx = 0;
	}

	while (rx > 1) { rx--; cx++; }
	while (rx < 0) { rx++; cx--; }

	// y
	ry += dy * dt;
	dy *= 0.96f;
	if (cy - 1 < 0 && ry <= 0.1f)
	{
		ry = 0.1f;
		dy = 0;
	}
	if (cy + 1 > 23 && ry >= 0.7f)
	{
		ry = 0.7f;
		dy = 0;
	}

	while (ry > 1) { ry--; cy++; }
	while (ry < 0) { ry++; cy--; }
}

void Entity::applyGravity(float dt)
{
	isGrounded = (cy + 1 > 23 && ry >= 0.7f);
	if (ignoreGravity || isGrounded || characterState == State::Jumping)
		return;
	float fallingSpeed = gravity * mass;
	dy += fallingSpeed;
	moved = true;
}

void Entity::manageState()
{
	characterState = State::Idle;
	if ((dx > 0.01f || dx < -0.01f) && characterState == State::Idle)
		characterState = State::Walking;
	if (dy > 0.01f)
		characterState = State::Falling;
	else if (dy < -0.01f)
		characterState = State::Jumping;

	moved = (!characterState == State::Idle);
}

void Entity::syncSprite(float dt)
{
	manageMovements(dt);
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
	applyGravity(dt);

	if (moved)
		syncSprite(dt);
	manageState();
}