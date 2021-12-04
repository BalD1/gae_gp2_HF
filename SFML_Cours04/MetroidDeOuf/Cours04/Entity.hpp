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

	sf::Sprite*			spr = nullptr;
	sf::Texture*		texture = nullptr;
	Hitbox*				hitbox = nullptr;

	std::string			name = "NONAME";
	float				maxHealth = 5;
	float				currentHealth = 5;
	float				speed = 0.5f;
	float				invincibility_CD = 1;
	float				invincibility_Timer = 0;

	bool				alive = true;
	bool				moved = false;

	std::string			tag = "";

#pragma region Grid

	int					cx = 0;
	int					cy = 0;
	float				rx = 0.0f;
	float				ry = 0.0f;

	float				xx = 0.0f;
	float				yy = 0.0f;

	float				dx = 0.0f;
	float				dy = 0.0f;

	int					stride = 16;

#pragma endregion


#pragma endregion

#pragma region Funcs

	Entity(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride);

	~Entity();

	void setTag(const std::string _tag);
	const std::string getTag();

	void manageMovements();

	void syncSprite();
	void render(sf::RenderTarget& target);

	void update(float dt);


#pragma endregion
};