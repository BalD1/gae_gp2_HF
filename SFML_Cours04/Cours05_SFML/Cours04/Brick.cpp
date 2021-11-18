#include "Brick.hpp"

Brick::Brick(sf::Texture& _texture, sf::Vector2f pos)
{
	this->spr = new sf::Sprite();
	this->spr->setTexture(_texture);

	this->spr->setOrigin(this->spr->getTexture()->getSize().x / 2, this->spr->getTexture()->getSize().y / 2);

	this->createHitbox(*this->spr, 0.0f, 0.0f, 50.0f, 25);
	verticalBox = new Hitbox(*this->spr, 0.0f, 0.0f, 25, 50);

	this->setPosition(pos);
}

Brick::Brick(sf::Texture& _texture, float posX, float posY)
{
	this->spr = new sf::Sprite();
	this->spr->setTexture(_texture);

	this->spr->setOrigin(this->spr->getTexture()->getSize().x / 2, this->spr->getTexture()->getSize().y / 2);

	this->createHitbox(*this->spr, -25, -20, 50.0f, 40);
	verticalBox = new Hitbox(*this->spr, -20, -25, 40, 50);

	this->setPosition(sf::Vector2f(posX, posY));
}

Brick::~Brick()
{

}

void Brick::update(float dt)
{
	this->hitbox->update();
	this->verticalBox->update();
}

void Brick::render(sf::RenderWindow& target, bool showHitbox)
{
	if (this == nullptr)
		return;
	target.draw(*this->spr);

	if (showHitbox)
	{
		this->hitbox->render(target);
		this->verticalBox->render(target);
	}
}
