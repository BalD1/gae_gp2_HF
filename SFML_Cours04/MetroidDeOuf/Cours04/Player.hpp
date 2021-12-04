#pragma once
#include "Entity.hpp"
class Player : public Entity
{
private:

	//vars

	float				jumpForce = -20;
	float				jumpLength = 0.5f;
	float				jumpTimer = 0;

	float				dt = 0;

	bool				canJump = true;

	//funcs

public:

	//vars


	//funcs

	Player(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride);
	~Player();

	void im();

	void render(sf::RenderTarget& target);
	void update(float dt);

	void manageInputs();
	void manageEventInputs(sf::Keyboard::Key key);
	void manageEventInputsRelease(sf::Keyboard::Key key);
	void jump();

};

