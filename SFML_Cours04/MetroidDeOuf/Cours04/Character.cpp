#include "Character.hpp"
#include "Game.hpp"

Character::Character(std::string _name, float _cx, float _cy, int _stride) :
	Entity(_cx, _cy, _stride)
{
	this->name = _name;
}

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
	this->ignoreGravity = _ignoreGravity;
}

void Character::setWorld(World* _worldRef)
{
	this->worldRef = _worldRef;
}


bool Character::isColliding(float _cx, float _cy)
{
	if (_cx <= 0)
		return true;
	if (_cy <= 0)
		return true;
	if (_cx >= 1280 / stride)
		return true;
	if (_cy >= 960 / stride)
		return true;

	if (worldRef != nullptr)
	{
		for (size_t i = 0; i < worldRef->entities.size(); ++i)
		{
			if (worldRef->entities[i]->cx == _cx && worldRef->entities[i]->cy == _cy)
				return true;
		}
	}	

	return false;
}

void Character::manageMovements(float dt)
{
	// x
	rx += dx * dt;
	dx *= frct_x * dt;

	if (isColliding(cx - 1, cy) && rx <= 0.01f)
	{
		rx = 0.01f;
		dx = 0;
	}
	if ((isColliding(cx + 1, cy) && rx >= 0.99f) || (isColliding(cx + 2, cy) && rx >= 0.99f))
	{
		rx = 0.99f;
		dx = 0;
	}

	while (rx > 1) { rx--; cx++; }
	while (rx < 0) { rx++; cx--; }

	// y
	ry += dy * dt;
	dy *= frict_y * dt;

	if ((isColliding(cx, cy -1) && ry <= 0.01f) || (isColliding(cx + 1, cy - 1) && ry <= 0.01f))
	{
		ry = 0.01f;
		dy = 0;
	}
	if ((isColliding(cx, cy + 1) && ry >= 0.01f) || (isColliding(cx + 1, cy + 1) && ry >= 0.01f) )
	{
		ry = 0.01f;
		dy = 0;
	}

	while (ry > 1) { ry--; cy++; }
	while (ry < 0) { ry++; cy--; }

	syncSprite(dt);
}

void Character::applyGravity(float dt)
{
	isGrounded = (isColliding(cx, cy + 1) || isColliding(cx + 1, cy + 1));
	if (ignoreGravity || isGrounded || characterState == State::Jumping)
		return;
	float fallingSpeed = worldRef->gravity * mass * fallingSpeedFactor;
	dy += fallingSpeed;
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

void Character::takeDamages(float rawDamages)
{
	this->currentHealth -= rawDamages;
	if (currentHealth <= 0)
	{
		kill();
	}
}

void Character::heal(float rawHeal)
{
	this->currentHealth = clamp(this->currentHealth + rawHeal, 0, this->maxHealth);
}

void Character::kill()
{
	delete(this);
}

void Character::update(float dt)
{
	applyGravity(dt);

	if (moved)
		manageMovements(dt);

	manageState();
}
