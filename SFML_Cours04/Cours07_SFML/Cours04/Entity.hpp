#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "Hitbox.hpp"
#include <iostream>

class Hitbox;

class Entity
{
private: 
	void init();

public:

#pragma region Variables

	sf::Sprite* spr = nullptr;
	Hitbox* hitbox = nullptr;

	float speed = 5;
	float invincibility_CD = 1;
	float invincibility_Timer = 0;

	bool alive = true;

	std::string tag = "";

#pragma endregion

#pragma region Funcs

	Entity();

	~Entity();

	void createHitbox(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height);

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);

	void setOrigin(const sf::Vector2f pos);
	void setOrigin(const float x, const float y);

	void setStats(float _speed, float _invincibilityCD);
	void setSpeed(float _speed);
	void setInvincibilityCD(float CD);

	void setTag(const std::string _tag);
	const std::string getTag();

	void move(const sf::Vector2f pos);
	void move(const float x, const float y);

	void kill();
	void revive();


#pragma endregion
};

//brick : entity
class EntityManager
{
public:
	std::vector<Entity*> repository;
};