#pragma once
#include "Entity.hpp"

class World
{
private:

	sf::Texture*			wallTexture = nullptr;

	int						mapLength = 50;
	int						stride = 32;


public:

	bool					worldInitialized = false;

	float					gravity = 0.7f;

	std::vector<Entity*>	entities;

	World(int _stride = 32);
	~World();

	void placeWall(int _cx, int _cy);

	void render(sf::RenderTarget& target);

};

