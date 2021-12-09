#include "Character.hpp"

Character::Character(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride) :
	Entity(_cx, _cy, _stride)
{
	this->name = _name;
	this->speed = _speed;
	this->invincibility_CD = _invicibilityCD;
	this->maxHealth = this->currentHealth = _maxHealth;
}

Character::~Character()
{
}

void Character::setGravity(float _gravity, bool _ignoreGravity)
{
	this->gravity = _gravity;
	this->ignoreGravity = _ignoreGravity;
}

void Character::setWorld(World* _worldRef)
{
	this->worldRef = _worldRef;
}


void Character::manageMovements(float dt)
{
	// x
	rx += dx * dt;
	dx *= 0.96f;
	if (worldRef->hasCollision(cx - 1, cy) && rx <= 0.1f)
	{
		rx = 0.1f;
		dx = 0;
	}
	if ((worldRef->hasCollision(cx + 2, cy) && rx >= 0.9f))
	{
		rx = 0.9f;
		dx = 0;
	}

	while (rx > 1) { rx--; cx++; }
	while (rx < 0) { rx++; cx--; }

	// y
	ry += dy * dt;
	dy *= 0.96f;
	if (worldRef->hasCollision(cx, cy - 1) && ry <= 0.05f)
	{
		ry = 0.05f;
		dy = 0;
	}
	if (worldRef->hasCollision(cx, cy + 1) && ry >= 0.05f)
	{
		ry = 0.05f;
		dy = 0;
	}

	while (ry > 1) { ry--; cy++; }
	while (ry < 0) { ry++; cy--; }
}

void Character::applyGravity(float dt)
{
	isGrounded = (worldRef->hasCollision(cx, cy + 1) && ry >= 0.05f);
	if (ignoreGravity || isGrounded || characterState == State::Jumping)
		return;
	float fallingSpeed = gravity * mass;
	dy += fallingSpeed;
	moved = true;
}

void Character::manageState()
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

void Character::syncSprite(float dt)
{
	manageMovements(dt);
	Entity::syncSprite(dt);
}

void Character::update(float dt)
{
	applyGravity(dt);

	if (moved)
		syncSprite(dt);
	manageState();
}
