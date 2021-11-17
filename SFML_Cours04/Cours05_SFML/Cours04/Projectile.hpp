#pragma once
#include "SFML/Graphics.hpp"
#include "Hitbox.hpp"
#include "Utility.hpp"
#include "Entity.hpp"
#include <iostream>

class Projectile
{
public:

	struct Data
	{
		Entity attachedEntity;
		sf::Sprite spr;
		Hitbox* hitbox = nullptr;
		sf::Vector2f direction = { 0,0 };
		sf::Vector2f offset = { 0,0 };
		std::vector<std::string> ignoreTags = { "" };
		float speed = 5;
		float damages = 1;
		bool activeSelf = false;
	};
	Data* projectileData = nullptr;

	Projectile(Entity _attachedEntity, sf::Texture _texture, sf::Vector2f _pos, sf::Vector2f _offset, sf::Vector2f _direction, float _speed, float _damages, bool _active);
	
	Hitbox* createHitbox(Data projectile, float offsetX, float offsetY, float width, float height);

	void setActive(bool active);
	const bool isActive();

	void addIgnoreTag(std::string tag);
	void addIgnoreTag(std::initializer_list<std::string> tags);

	void update(const float& dt);
	void render(sf::RenderWindow& target, bool showHitbox);

	void move(const float& dt);
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	sf::Vector2f getPosition();

	void inverseDirection(sf::Vector2f _dir);

	void bounce(const sf::Vector2f target);

private:

};