#include "Character.hpp"

Character::Character(std::string _name, float _cx, float _cy, int _stride) :
	Entity(_cx, _cy, _stride)
{
	this->name = _name;
	setState(new IdleState(this));
}

Character::Character(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride) :
	Entity(_cx, _cy, _stride)
{
	this->name = _name;
	this->speed = _speed;
	this->invincibility_CD = _invicibilityCD;
	this->maxHealth = this->currentHealth = _maxHealth;

	setState(new IdleState(this));
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


bool Character::isCollidingWithWorld(float _cx, float _cy)
{
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

bool Character::isCollidingSelf(float _cx, float _cy)
{
	if (cx == _cx && cy == _cy)
		return true;
	return false;
}

void Character::manageMovements(float dt)
{
	// x
	rx += dx * dt;
	dx *= frct_x * dt;

	if (isCollidingWithWorld(cx - 1, cy) && rx <= 0.01f)
	{
		rx = 0.01f;
		dx = 0;
	}
	if ((isCollidingWithWorld(cx + 1, cy) && rx >= 0.99f) || (isCollidingWithWorld(cx + 2, cy) && rx >= 0.99f))
	{
		rx = 0.99f;
		dx = 0;
	}

	while (rx > 1) { rx--; cx++; }
	while (rx < 0) { rx++; cx--; }

	// y
	ry += dy * dt;
	dy *= frict_y * dt;

	if ((isCollidingWithWorld(cx, cy -1) && ry <= 0.01f) || (isCollidingWithWorld(cx + 1, cy - 1) && ry <= 0.01f))
	{
		ry = 0.01f;
		dy = 0;
	}
	if ((isCollidingWithWorld(cx, cy + 1) && ry >= 0.01f) || (isCollidingWithWorld(cx + 1, cy + 1) && ry >= 0.01f) )
	{
		ry = 0.01f;
		dy = 0;
	}

	while (ry > 1) { ry--; cy++; }
	while (ry < 0) { ry++; cy--; }

	syncTransform();
}

void Character::applyGravity(float dt)
{
	isGrounded = (isCollidingWithWorld(cx, cy + 1) || isCollidingWithWorld(cx + 1, cy + 1));
	if (ignoreGravity || isGrounded || characterState == State::Jumping)
	{
		fallingSpeed = 0;
		return;
	}
	fallingSpeed += clamp(worldRef->gravity * mass * fallingSpeedFactor * dt, 0, maxFallingSpeed);
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

void Character::syncTransform()
{
	xx = (cx + rx) * stride;
	yy = (cy + ry) * stride;
	this->setPosition(xx, yy);
}

void Character::takeDamages(float rawDamages)
{
	if (invincibility_Timer <= 0)
	{
		this->currentHealth -= rawDamages;
		invincibility_Timer = invincibility_CD;
	}
}

void Character::heal(float rawHeal)
{
	this->currentHealth = clamp(this->currentHealth + rawHeal, 0, this->maxHealth);
}

void Character::update(float dt)
{
	if (invincibility_Timer > 0)
		invincibility_Timer -= dt;

	applyGravity(dt);

	if (moved)
		manageMovements(dt);

	manageState();

	currentState->onUpdate(dt);

	if (target != std::nullopt || curPath.size())
	{
		if (std::nullopt != target)
		{
			sf::Vector2f tgtF(target->x * stride, target->y * stride);
			if (cx == target->x && cy == target->x)
			{
				target = std::nullopt;
			}
			else
			{
				float diffX = (cx - target->x);
				float diffY = (cy - target->y);
				float angle = atan2(diffY, diffX);
				dx = cos(angle) * 3;
				dy = sin(angle) * 3;
			}
			return;
		}
		else
		{
			target = curPath[0];
			curPath.erase(curPath.begin());
		}
	}
}

void Character::render(sf::RenderTarget& target)
{
	sf::RenderStates states;
	states.transform *= getTransform();
	target.draw(*this->spr, states);
}

void Character::setState(States* newState)
{
	if (currentState)
		delete currentState;

	currentState = newState;
	currentState->onEnter();
}

void States::checkIfCreated()
{
	if (c->texture == nullptr)
		c->texture = new sf::Texture();
	if (c->spr == nullptr)
		c->spr = new sf::Sprite();
}

void IdleState::onEnter()
{
	checkIfCreated();

	c->texture->loadFromFile("Assets/Graphs/idle.png");
	c->spr->setTexture(*c->texture);
	cover_TIMER = cover_CD;
}

void IdleState::onUpdate(float dt)
{
	cover_TIMER -= dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		c->setState(new WalkState(c));
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		c->setState(new WalkState(c));
		return;
	}

	if (cover_TIMER <= 0)
	{
		if (c->isCollidingWithWorld(c->cx + 2, c->cy) || c->isCollidingWithWorld(c->cx - 2, c->cy))
		{
			c->setState(new CoverState(c));
			return;
		}
	}
}

void WalkState::onEnter()
{
	checkIfCreated();

	c->texture->loadFromFile("Assets/Graphs/walk.png");
	c->spr->setTexture(*c->texture);
}

void WalkState::onUpdate(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		c->dx = c->speed * -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		c->dx = c->speed;
	}
	if (-0.01f < c->dx && c->dx < 0.01f)
	{
		c->setState(new IdleState(c));
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		c->setState(new RunState(c));
		return;
	}
		
}

void RunState::onEnter()
{
	checkIfCreated();

	c->texture->loadFromFile("Assets/Graphs/run.png");
	c->spr->setTexture(*c->texture);
}

void RunState::onUpdate(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		c->dx = c->speed * -2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		c->dx = c->speed * 2;
	}
	if (-0.01f < c->dx && c->dx < 0.01f)
	{
		c->setState(new IdleState(c));
		return;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		c->setState(new WalkState(c));
		return;
	}
}

void CoverState::onEnter()
{
	checkIfCreated();

	c->texture->loadFromFile("Assets/Graphs/cover.png");
	c->spr->setTexture(*c->texture);
}

void CoverState::onUpdate(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		c->setState(new WalkState(c));
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		c->setState(new WalkState(c));
		return;
	}
}
