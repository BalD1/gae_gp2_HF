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
	if (_cx > mapLength || _cy > mapLength)
		return;
	for (size_t i = 0; i < entities.size(); ++i)
	{
		if (entities[i]->cx == _cx && entities[i]->cy == _cy)
			return;
	}
	Entity* wall = new Entity(_cx, _cy, stride, wallTexture);
	entities.push_back(wall);
}

void World::render(sf::RenderTarget& target)
{
	for (std::size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->render(target);
	}
}

