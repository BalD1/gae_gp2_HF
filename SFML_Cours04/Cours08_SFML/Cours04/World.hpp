#pragma once
#include "Entity.hpp"
#include "DeathZone.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <optional>

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

	float length(const sf::Vector2i& s);

	std::vector<Entity*> map;

	std::unordered_map<sf::Vector2i, bool>			grid;
	std::unordered_map<sf::Vector2i, float>			distance;
	std::unordered_map<sf::Vector2i, sf::Vector2i>	pr;

	std::vector<sf::Vector2i> queue;

	bool isColliding(int _cx, int _cy);

	void init(const sf::Vector2i& start);
	void relax(sf::Vector2i& s1, sf::Vector2i& s2);
	std::optional<sf::Vector2i> findMin(std::vector<sf::Vector2i>& q);
	void compute(const sf::Vector2i& start);
};

class Enemy;

class World
{
private:


	sf::Texture*				wallTexture = nullptr;
	sf::Texture*				deathzoneTexture = nullptr;

	int							mapLength = 50;
	int							stride = 32;


public:

	static std::vector<sf::Vector2i> currentPath;
	static Dijkstra				dij;

	bool						worldInitialized = false;
	bool						renderDeathZones = false;

	float						gravity = 0.7f;

	std::vector<Entity*>		entities;
	static std::vector<Entity*>		walls;
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

