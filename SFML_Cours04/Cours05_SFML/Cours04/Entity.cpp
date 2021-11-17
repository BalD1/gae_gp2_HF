#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "Entity.hpp"

void Entity::init()
{
	this->hitbox = nullptr;
	this->spr = nullptr;
}

Entity::Entity()
{
	init();
}

Entity::~Entity()
{
}

void Entity::createHitbox(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height)
{
	this->hitbox = new Hitbox(sprite, offsetX, offsetY, width, height);
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitbox)
		return this->hitbox->getPosition();

	if (this->spr)
		return this->spr->getPosition();
}

void Entity::setPosition(const sf::Vector2f pos)
{
	this->hitbox->setPosition(pos);
	this->spr->setPosition(pos);
}
void Entity::setPosition(const float x, const float y)
{
	this->hitbox->setPosition(x, y);
	this->spr->setPosition(x, y);
}

void Entity::setOrigin(const sf::Vector2f pos)
{
	this->spr->setOrigin(pos);
}

void Entity::setOrigin(const float x, const float y)
{
}

void Entity::setStats(float _speed, float _invincibilityCD)
{
	speed = _speed;
	invincibility_CD = _invincibilityCD;
}

void Entity::setSpeed(float _speed)
{
	speed = _speed;
}

void Entity::setInvincibilityCD(float CD)
{
	invincibility_CD = CD;
}

void Entity::setTag(const std::string _tag)
{
	this->tag = _tag;
}

const std::string Entity::getTag()
{
	return this->tag;
}

void Entity::move(const sf::Vector2f pos)
{
	this->spr->move(pos * speed);
}
 void Entity::move(const float x, const float y)
{
	this->spr->move(x * speed, y * speed);
}

 void Entity::kill()
 {
	 alive = false;
 }

 void Entity::revive()
 {
	 alive = true;
 }
