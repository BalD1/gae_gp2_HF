#pragma once
#include "Entity.hpp"
#include "World.hpp"

class Character : public Entity
{
private:


public:

	std::string			name = "NONAME";
	float				maxHealth = 5;
	float				currentHealth = 5;
	float				speed = 7.5f;
	float				invincibility_CD = 1;
	float				invincibility_Timer = 0;
	float				mass = 1;
	float				frct_x = 0.86f;
	float				frct_y = 0.96f;
	float				fallingSpeedFactor = 3;

	bool				alive = true;
	bool				moved = false;
	bool				isGrounded = false;
	bool				ignoreGravity = false;

	enum				State { Idle, Walking, Jumping, Falling };
	State				characterState = Idle;

	World*				worldRef = nullptr;

	Character(std::string _name, float _cx, float _cy, int _stride);
	Character(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride);
	~Character();

	void setGravity(float _gravity, bool _ignoreGravity = false);
	void setWorld(World* _worldRef);

	bool isColliding(float _cx, float _cy);
	void manageMovements(float dt);
	void applyGravity(float dt);
	void manageState();

	void takeDamages(float rawDamages);
	void heal(float rawHeal);
	void kill();

	void update(float dt);

};

