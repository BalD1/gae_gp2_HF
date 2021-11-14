#include "Weapon.hpp"

Weapon::Weapon(sf::Texture& _texture, float _fireCD, int _projectileNum, sf::Vector2f pos, Entity& _attachedEntity)
{
	this->spr = new sf::Sprite();
	this->spr->setTexture(_texture);

	this->spr->setPosition(pos);
	this->attachedEntity = &_attachedEntity;

	fireCD = _fireCD;
}

Weapon::Weapon(sf::Texture& _texture, float _fireCD, int _projectileNum, float posX, float posY, Entity& _attachedEntity)
{
	this->spr = new sf::Sprite();
	this->spr->setTexture(_texture);

	this->spr->setPosition(posX, posY);
	this->attachedEntity = &_attachedEntity;

	fireCD = _fireCD;

	sf::Texture projectileTexture;
	if (!projectileTexture.loadFromFile("Assets/bullet.png"))
	{
		std::cout << "Could not load projectile texture";
	}
}

Weapon::~Weapon()
{
	delete this->spr;
}

void Weapon::fire(Projectile* _projectiles, sf::Vector2f dir)
{
	if (fireTimer <= 0)
	{
		fireTimer = fireCD;				
		sf::Texture projectileTexture;
		if (!projectileTexture.loadFromFile("Assets/bullet.png"))
		{
			std::cout << "Could not load projectile texture";
		}
		_projectiles->createProjectile(projectileTexture, this->getPosition(), dir, 5, 1, true);

	}
}

void Weapon::setOffset(const sf::Vector2f _offset)
{
	this->offset = _offset;
	this->setPosition(this->spr->getPosition());
}

void Weapon::setOffset(const float x, const float y)
{
	this->offset.x = x;
	this->offset.y = y;
	this->setPosition(this->spr->getPosition());
}

void Weapon::setPosition(sf::Vector2f pos)
{
	this->spr->setPosition(pos + offset);
}

void Weapon::setPosition(float x, float y)
{
	this->spr->setPosition(x + offset.x, y + offset.y);
}

sf::Vector2f Weapon::getPosition()
{
	return this->spr->getPosition();
}

void Weapon::lookAt(const sf::Vector2f target)
{
	sf::Vector2f offset = this->spr->getPosition();
	offset.x -= target.x;
	offset.y -= target.y;

	float angle = atan2(-offset.y, -offset.x) * (360 / (3.14 * 2));

	this->spr->setRotation(angle);
}

void Weapon::lookAt(const float targetX, const float targetY)
{
	sf::Vector2f offset = this->spr->getPosition();
	offset.x -= targetX;
	offset.y -= targetY;

	float angle = atan2(-offset.y, -offset.x) * (360 / (3.14 * 2));

	this->spr->setRotation(angle);
}

void Weapon::update(float dt)
{
	if (fireTimer >= 0)
		fireTimer -= dt;

	this->setPosition(attachedEntity->getPosition());
}

void Weapon::render(sf::RenderWindow& target, bool showHitbox)
{
	target.draw(*this->spr);
}
