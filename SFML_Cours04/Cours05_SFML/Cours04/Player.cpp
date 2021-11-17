#include "Player.hpp"

Player::Player(sf::Texture& _texture, sf::Vector2f pos, bool originAtCenter)
{
	this->spr = new sf::Sprite();
	this->spr->setTexture(_texture);
	if (originAtCenter)
		this->spr->setOrigin(this->spr->getTexture()->getSize().x / 2, this->spr->getTexture()->getSize().y / 2);

	this->createHitbox(*this->spr, -75, -12, 150.0f, 25.0f);

	this->setPosition(pos);
}
Player::Player(sf::Texture& _texture, float posX, float posY, bool originAtCenter)
{
	this->spr = new sf::Sprite();
	this->spr->setTexture(_texture);
	if (originAtCenter)
		this->spr->setOrigin(this->spr->getTexture()->getSize().x / 2, this->spr->getTexture()->getSize().y / 2);

	this->createHitbox(*this->spr, -75, -20, 150.0f, 25.0f);

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
