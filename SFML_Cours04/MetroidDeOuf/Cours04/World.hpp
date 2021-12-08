#pragma once
#include "Entity.hpp"

class World
{
private:

	sf::Texture*			wallTexture = nullptr;

	Entity*					walls[20][20] = {};

	int						stride = 32;

public:

	World(int _stride = 32);
	~World();

	void placeWall(int _cx, int _cy);

	bool hasCollision(int cx, int cy);

	void render(sf::RenderTarget& target);

};

