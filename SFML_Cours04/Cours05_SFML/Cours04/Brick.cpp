#include "Brick.hpp"

Brick::Brick(sf::Texture& _texture, sf::Vector2f pos)
{
	this->spr = new sf::Sprite();
	this->spr->setTexture(_texture);

	this->createHitbox(*this->spr, 0.0f, 0.0f, 50.0f, 50.0f);

	this->setPosition(pos);
}

Brick::Brick(sf::Texture& _texture, float posX, float posY)
{
	this->spr = new sf::Sprite();
	this->spr->setTexture(_texture);

	this->createHitbox(*this->spr, 0.0f, 0.0f, 50.0f, 50.0f);

	this->setPosition(sf::Vector2f(posX, posY));
}

Brick::~Brick()
{

}

void Brick::update(float dt)
{

}

void Brick::render(sf::RenderWindow& target, bool showHitbox)
{
	if (this == nullptr)
		return;
	target.draw(*this->spr);

	if (showHitbox)
	{
		this->hitbox->render(target);
	}
}
