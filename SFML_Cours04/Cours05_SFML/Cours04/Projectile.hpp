#pragma once
#include "SFML/Graphics.hpp"
#include "Hitbox.hpp"
#include <iostream>

class Projectile
{
public:

	struct projData
	{
		sf::Sprite spr;
		Hitbox* hitbox;
		sf::Vector2f direction = { 0,0 };
		std::vector<std::string> ignoreTags = { "" };
		float speed = 5;
		float damages = 1;
		bool activeSelf = false;
	};

	int projectilesNumber = 0;

	std::vector<projData>* projectiles;

	Projectile();

	void createProjectile(sf::Texture _texture, sf::Vector2f _pos, sf::Vector2f _direction, float _speed, float _damages, bool _active);
	
	Hitbox* createHitbox(projData projectile, float offsetX, float offsetY, float width, float height);

	void setActive(int idx, bool active);
	const bool isActive(int idx);

	void addIgnoreTag(int idx, std::string tag);
	void addIgnoreTag(int idx, std::initializer_list<std::string> tags);

	void update(const float& dt);
	void render(sf::RenderWindow& target, bool showHitbox);

	void move(int idx);
	void setPosition(int idx, const sf::Vector2f pos);
	void setPosition(int idx, const float x, const float y);
	sf::Vector2f getPosition(int idx);

	void bounce();

private:

};