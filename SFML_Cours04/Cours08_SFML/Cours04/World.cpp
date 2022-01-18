#include "World.hpp"
#include "Enemy.hpp"

Dijkstra World::dij;
std::vector<Entity*> World::walls;
std::vector<sf::Vector2i> World::currentPath;

World::World(int _stride)
{

	this->stride = _stride;

	this->wallTexture = new sf::Texture();
	if (!wallTexture->loadFromFile("Assets/Graphs/mur.png"))
		printf("Mur texture could not be loaded in Assets/Graphs/mur.png");
	this->deathzoneTexture = new sf::Texture();
	if (!deathzoneTexture->loadFromFile("Assets/Graphs/deathzone.png"))
		printf("Mur texture could not be loaded in Assets/Graphs/deathzone.png");

}

World::~World()
{
}

bool World::colidesWithWall(Entity target)
{
	for (auto w : entities)
	{
		if (target.cx == w->cx && target.cy == w->cy)
			return true;
	}
	return false;
}

void World::placeDeathZone(int _cx, int _cy)
{
	if (_cx > mapLength || _cy > mapLength)
		return;
	for (size_t i = 0; i < deathZones.size(); ++i)
	{
		if (deathZones[i]->cx == _cx && deathZones[i]->cy == _cy)
		{
			delete(deathZones[i]);
			deathZones.erase(deathZones.begin() + i);
			return;
		}
	}
	DeathZone* dz = new DeathZone(_cx, _cy, stride, *deathzoneTexture);
	deathZones.push_back(dz);
}

void World::placeWall(int _cx, int _cy)
{
	if (_cx > mapLength || _cy > mapLength)
		return;
	for (size_t i = 0; i < entities.size(); ++i)
	{
		if (entities[i]->cx == _cx && entities[i]->cy == _cy)
		{
			delete(entities[i]);
			entities.erase(entities.begin() + i);
			return;
		}
	}
	Entity* wall = new Entity(_cx, _cy, stride, wallTexture);
	entities.push_back(wall);
}

void World::eraseMap()
{
	for (Entity* e : entities)
		delete(e);
	entities.clear();
	for (DeathZone* dz : deathZones)
		delete(dz);
	deathZones.clear();
}

void World::deleteEntities()
{
	for (auto e : entitiesToDelete)
		delete(e);
}

void World::render(sf::RenderTarget& target)
{
	for (auto e : entities)
		e->render(target);
	if (renderDeathZones)
	{
		for (auto dz : deathZones)
			dz->render(target);
	}

	sf::VertexArray arr;
	arr.setPrimitiveType(sf::Lines);
	for (auto& p : dij.pr)
	{
		sf::Vertex start;
		sf::Vertex end;
		start.color = sf::Color::Green;
		start.color.a = 127;

		end.color = start.color;

		start.position.x = (p.first.x + 0.5f) * 32;
		start.position.y = (p.first.y + 0.5f) * 32;

		end.position.x = (p.second.x + 0.5f) * 32;
		end.position.y = (p.second.y + 0.5f) * 32;

		arr.append(start);
		arr.append(end);
	}
	target.draw(arr);
}

void World::saveMapInFile(const char* filePath)
{
	FILE* f = nullptr;
	fopen_s(&f, filePath, "wb");
	if (f)
	{
		std::string entityData = "";

		if (entities.size() > 0)
		{
			for (Entity* e : entities)
			{
				entityData = "";
				if (e->texture == wallTexture)
					entityData += "wall ";

				entityData += std::to_string(e->cx) + " " + std::to_string(e->cy) + "\n";
				fprintf(f, entityData.c_str());
			}
			for (DeathZone* dz : deathZones)
			{
				entityData = "";
				entityData += "deathzone ";

				entityData += std::to_string(dz->cx) + " " + std::to_string(dz->cy) + "\n";
				fprintf(f, entityData.c_str());
			}
		}
		fflush(f);
		fclose(f);
	}
}

void World::loadMap(const char* filePath, bool eraseCurrentMap)
{
	worldInitialized = false;
	if (eraseCurrentMap)
		eraseMap();

	FILE* f = nullptr;
	fopen_s(&f, filePath, "rb");
	if (f)
	{
		char line[256] = {};
		while (true)
		{
			int64_t _cx = 0;
			int64_t _cy = 0;
			fscanf_s(f, "%s %lld %lld\n", line, 256, &_cx, &_cy);
			if (strcmp(line, "wall") == 0)
			{
				Entity* w = new Entity(_cx, _cy, stride, wallTexture);
				entities.push_back(w);
				walls.push_back(w);
			}
			else if (strcmp(line, "deathzone") == 0)
			{
				DeathZone* dz = new DeathZone(_cx, _cy, stride, *deathzoneTexture);
				deathZones.push_back(dz);
			}

			if (feof(f))
				break;
		}
		fclose(f);
	}


	worldInitialized = true;
}

float Dijkstra::length(const sf::Vector2i& s)
{
	return sqrt(s.y * s.y + s.x * s.x);
}

bool Dijkstra::isColliding(int _cx, int _cy)
{
	for (auto w : World::walls)
	{
		if (w->cx == _cx && w->cy == _cy)
			return true;
	}
	return false;
}

void Dijkstra::init(const sf::Vector2i& start)
{
	for (auto& act : grid)
	{
		distance[act.first] = 1024 * 1024;
		queue.push_back(act.first);
	}

	distance[start] = 0;
}

void Dijkstra::relax(sf::Vector2i& s1, sf::Vector2i& s2)
{
	float dist_s1s2 = length(s2 - s1);
	if (distance[s2] > (distance[s1] + dist_s1s2))
	{
		distance[s2] = distance[s1] + dist_s1s2;
		pr[s2] = s1;
	}
}

std::optional<sf::Vector2i> Dijkstra::findMin(std::vector<sf::Vector2i>& q)
{
	std::optional<sf::Vector2i> res = std::nullopt;
	float distMin = 1024 * 1024;
	for (auto& act : q)
	{
		if (distance[act] < distMin)
		{
			distMin = distance[act];
			res = act;
		}
	}
	return res;
}

void Dijkstra::compute(const sf::Vector2i& start)
{
	grid.clear();

	int max_WIDTH = 1600 / 32 + 1;
	int max_HEIGHT = 900 / 32 + 1;
	for (int y = 0; y < max_HEIGHT; ++y)
	{
		for (int x = 0; x < max_WIDTH; ++x)
		{
			if (!isColliding(x, y))
				grid[sf::Vector2i(x, y)] = true;
		}
	}

	queue.clear();
	distance.clear();
	pr.clear();

	init(start);

	while (!queue.empty())
	{
		std::optional<sf::Vector2i> act = findMin(queue);
		if (act == std::nullopt)
			break;

		auto pos = std::find(queue.begin(), queue.end(), *act);
		if (pos != queue.end())
			queue.erase(pos);

		sf::Vector2i directions[] =
		{
			sf::Vector2i(0,1),  sf::Vector2i(1,0),
			sf::Vector2i(0,-1), sf::Vector2i(-1,0),
		};

		for (int i = 0; i < 4; i++)
		{
			sf::Vector2i neighbor = *act + directions[i];
			if (grid.find(neighbor) != grid.end())
				relax(*act, neighbor);
		}
	}
	int here = 0;
}
