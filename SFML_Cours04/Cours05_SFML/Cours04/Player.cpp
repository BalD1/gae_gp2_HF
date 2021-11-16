#include "Player.hpp"

Player::Player(sf::Texture& _texture, sf::Vector2f pos)
{
	this->spr = new sf::Sprite();
	this->spr->setTexture(_texture);

	this->createHitbox(*this->spr, 0.0f, 0.0f, 50.0f, 50.0f);

	this->setPosition(pos);
}
Player::Player(sf::Texture& _texture, float posX, float posY)
{
	this->spr = new sf::Sprite();
	this->spr->setTexture(_texture);

	this->createHitbox(*this->spr, 0.0f, 0.0f, 50.0f, 50.0f);

	this->setPosition(posX, posY);
}

Player::~Player()
{

}

void Player::update(const float& dt)
{
	this->hitbox->update();
}

void Player::render(sf::RenderTarget& target, const bool showHitbox)
{
	target.draw(*this->spr);

	if (showHitbox)
		this->hitbox->render(target);
}
