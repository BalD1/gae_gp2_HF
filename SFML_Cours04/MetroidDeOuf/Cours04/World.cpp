#include "World.hpp"

World::World(int _stride)
{
	this->stride = _stride;

	this->wallTexture = new sf::Texture();
	if (!wallTexture->loadFromFile("Assets/Graphs/mur.png"))
		printf("Mur texture could not be loaded in Assets/Graphs/mur.png");
}

World::~World()
{
}

void World::placeWall(int _cx, int _cy)
{
	Entity* wall = new Entity(_cx, _cy, stride, wallTexture);
	walls[_cx][_cy] = wall;
}

bool World::hasCollision(int cx, int cy)
{
	if (walls[cx][cy] != nullptr)
		return true;
	return false;
}

void World::render(sf::RenderTarget& target)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (walls[i][j] != nullptr)
				walls[i][j]->render(target);
		}
	}
}

