#pragma once

#include "SFML/Graphics.hpp"
#include "Projectile.hpp"
#include "Entity.hpp"
#include <list>

class Weapon
{
public:

	sf::Sprite* spr = nullptr;

	Entity* attachedEntity = nullptr;

	sf::Vector2f offset = sf::Vector2f(0,0);

	float fireCD = 0.5f;
	float fireTimer = 0;

	Weapon(sf::Texture& _texture, float _fireCD, int _projectileNum, sf::Vector2f pos, Entity& _attachedEntity);
	Weapon(sf::Texture& _texture, float _fireCD, int _projectileNum, float posX, float posY, Entity& _attachedEntity);
	~Weapon();

	void fire(Projectile* _projectiles, sf::Vector2f dir);

	void setOffset(const sf::Vector2f _offset);
	void setOffset(const float x, float y);

	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);

	sf::Vector2f getPosition();

	void lookAt(const sf::Vector2f target);
	void lookAt(const float targetX, const float targetY);

	void update(float dt);
	void render(sf::RenderWindow& target, bool showHitbox);

private:

};