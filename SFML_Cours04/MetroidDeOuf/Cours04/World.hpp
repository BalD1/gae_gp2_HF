#pragma once
#include "Entity.hpp"
#include "DeathZone.hpp"

class World
{
private:

	sf::Texture*				wallTexture = nullptr;

	int							mapLength = 50;
	int							stride = 32;


public:

	bool						worldInitialized = false;
	bool						renderDeathZones = false;

	float						gravity = 0.7f;

	std::vector<Entity*>		entities;
	std::vector<DeathZone*>		deathZones;

	World(int _stride = 32);
	~World();

	void placeDeathZone(int _cx, int _cy);
	void placeWall(int _cx, int _cy);
	void eraseMap();

	void render(sf::RenderTarget& target);

	// files
	void saveMapInFile(const char* filePath);
	void loadMap(const char* filePath, bool eraseCurrentMap = true);

};

