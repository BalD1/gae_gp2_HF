#pragma once
#include "stdafx.hpp"
#include "Bullet.hpp"
#include "World.hpp"

class Weapon
{
private:

	sf::RectangleShape*				spr = nullptr;
	sf::Vector2f					offset = { 0,0 };

	std::vector<Bullet*>			bulletsPool;
	int								poolCount = 10;

	float							fireCD = 0.1f;
	float							CDtimer = 0;

	float							cx;
	float							rx;
	float							cy;
	float							ry;


public:

	sf::Vector2f					mousePosition;
	int								stride = 32;

	Weapon();
	~Weapon();

	void setPosition(float _cx, float _rx, float _cy, float _ry);
	void setOffset(sf::Vector2f _offset);
	void lookAtMouse();

	void fire();
	void setBullet(Bullet* bullet);

	void update(float dt);
	void render(sf::RenderTarget& target, sf::RenderStates states);
};

