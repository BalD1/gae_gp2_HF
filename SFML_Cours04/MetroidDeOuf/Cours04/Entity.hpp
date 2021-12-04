#pragma once
#include "stdafx.hpp"

class Hitbox;

class Entity
{
private: 
	void init();

public:

#pragma region Variables

	sf::Sprite*			spr = nullptr;
	sf::Texture*		texture = nullptr;

	std::string			name = "NONAME";
	float				maxHealth = 5;
	float				currentHealth = 5;
	float				speed = 0.5f;
	float				invincibility_CD = 1;
	float				invincibility_Timer = 0;
	float				gravity = 0.5f;
	float				mass = 1;

	bool				alive = true;
	bool				moved = false;
	bool				isGrounded = false;
	bool				ignoreGravity = false;

	std::string			tag = "";

	enum State			{ Idle, Walking, Jumping, Falling};
	State				characterState = Idle;

#pragma region Grid
						// grid coordinates
	int					cx = 0;
	int					cy = 0;
						// ratios of player position inside cells
	float				rx = 0.0f;
	float				ry = 0.0f;

						// coordinates from (cx+rx) : (cy+ry)
	float				xx = 0.0f;
	float				yy = 0.0f;

						// movements
	float				dx = 0.0f;
	float				dy = 0.0f;

	int					stride = 16;

#pragma endregion


#pragma endregion

#pragma region Funcs

	Entity(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride);

	~Entity();

	void setGravity(float _gravity, bool _ignoreGravity = false);
	void setTag(const std::string _tag);
	const std::string getTag();

	void manageMovements(float dt);
	void applyGravity(float dt);
	void manageState();

	void syncSprite(float dt);
	void render(sf::RenderTarget& target);

	void update(float dt);


#pragma endregion
};