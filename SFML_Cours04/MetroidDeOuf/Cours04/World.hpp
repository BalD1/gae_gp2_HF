#pragma once
#include "Entity.hpp"

class World
{
private:

	sf::Texture*			wallTexture = nullptr;
	sf::CircleShape			cs;

	int						mapLength = 50;
	Entity*					walls[50][50];

	int						stride = 32;

public:

	World(int _stride = 32);
	~World();

	void placeWall(int _cx, int _cy);

	bool hasCollision(int cx, int cy);

	void render(sf::RenderTarget& target);

};

