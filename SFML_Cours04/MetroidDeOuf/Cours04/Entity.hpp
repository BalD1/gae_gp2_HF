#pragma once
#include "stdafx.hpp"
#include "Hitbox.hpp"

class Hitbox;

class Entity
{
private: 
	void init();

public:

#pragma region Variables

	sf::Sprite* spr = nullptr;
	Hitbox* hitbox = nullptr;

	std::string name = "NONAME";
	float maxHealth = 5;
	float currentHealth = 5;
	float speed = 5;
	float invincibility_CD = 1;
	float invincibility_Timer = 0;

	bool alive = true;

	std::string tag = "";

#pragma endregion

#pragma region Funcs

	Entity(std::string _name, float _speed, float _invicibilityCD, float _maxHealth);

	~Entity();

	void createHitbox(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height);

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);

	void setOrigin(const sf::Vector2f pos);
	void setOrigin(const float x, const float y);

	void setTag(const std::string _tag);
	const std::string getTag();

	void move(const sf::Vector2f pos);
	void move(const float x, const float y);

	void kill();
	void revive();


#pragma endregion
};