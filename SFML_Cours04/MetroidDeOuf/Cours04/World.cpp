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
	if (walls[_cx][_cy] != nullptr)
		return;
	if (_cx > mapLength || _cy > mapLength)
		return;

	Entity* wall = new Entity(_cx, _cy, stride, wallTexture);
	cs = sf::CircleShape(2);
	cs.setFillColor(sf::Color::Red);
	walls[_cx][_cy] = wall;
}

bool World::hasCollision(int cx, int cy)
{
	if (this == nullptr || walls == nullptr)
		return false;

	if (walls[cx][cy] != nullptr)
		return true;

	return false;
}

void World::render(sf::RenderTarget& target)
{
	for (int i = 0; i < mapLength; i++)
	{
		for (int j = 0; j < mapLength; j++)
		{
			if (walls[i][j] != nullptr)
			{
				cs.setPosition(walls[i][j]->spr->getPosition());
				walls[i][j]->render(target);
				target.draw(cs);
			}
		}
	}
}

