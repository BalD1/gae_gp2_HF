#pragma once
#include "Entity.hpp"
#include "DeathZone.hpp"
#include <unordered_map>

namespace std {
	template <>
	struct hash<sf::Vector2i> {
		std::size_t operator()(const sf::Vector2i& k) const {
			using std::size_t;
			using std::hash;
			using std::string;
			return k.x | (k.y << 12);
		}
	};
}

class Dijkstra {
public:
	std::unordered_map<sf::Vector2i, bool>			g;
	std::unordered_map<sf::Vector2i, float>			dist;

	void compute();
};

class Enemy;

class World
{
private:

	static Dijkstra				dij;

	sf::Texture*				wallTexture = nullptr;
	sf::Texture*				deathzoneTexture = nullptr;

	int							mapLength = 50;
	int							stride = 32;


public:

	bool						worldInitialized = false;
	bool						renderDeathZones = false;

	float						gravity = 0.7f;

	std::vector<Entity*>		entities;
	std::vector<Entity*>		entitiesToDelete;
	std::vector<DeathZone*>		deathZones;

	World(int _stride = 32);
	~World();

	bool colidesWithWall(Entity target);

	void placeDeathZone(int _cx, int _cy);
	void placeWall(int _cx, int _cy);
	void eraseMap();

	void deleteEntities();

	void render(sf::RenderTarget& target);

	// files
	void saveMapInFile(const char* filePath);
	void loadMap(const char* filePath, bool eraseCurrentMap = true);

};

