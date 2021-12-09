#include "Character.hpp"
#include "Game.hpp"

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
	dx *= 0.96f;
	while (rx >= 1) 
	{
		if (isColliding(cx + 2, cy)) 
		{
			dx = 0;
			rx = 0.95;
		}
		else {
			rx--;
			cx++;
		}
	}
	while (rx <= 0) 
	{
		if (isColliding(cx - 1, cy))
		{
			dx = 0;
			rx = 0.05;
		}
		else {
			rx++;
			cx--;
		}
	}

	// y
	ry += dy * dt;
	dy *= 0.96f;
	while (ry >= 1) 
	{
		if (isColliding(cx, cy + 1))
		{
			dy = 0;
			ry = 0.95f;
		}
		else {
			ry--;
			cy++;
		}
	}
	while (ry <= 0) 
	{
		if (isColliding(cx, cy - 1)) 
		{
			dy = 0.0f;
			ry = 0.05f;
		}
		else {
			ry++;
			cy--;
		}
	}
}

void Character::applyGravity(float dt)
{
	isGrounded = (isColliding(cx, cy + 1));
	if (ignoreGravity || isGrounded || characterState == State::Jumping)
		return;
	float fallingSpeed = worldRef->gravity * mass;
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
