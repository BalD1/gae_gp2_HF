#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Shape.hpp"
class Entity
{
public:
	sf::Shape* spr = nullptr;
	sf::FloatRect hitBox;

	Entity(sf::Shape* _spr)
	{
		//hitbox
	}
};

//brick : entity
class EntityManager
{
public:
	std::vector<Entity*> repository;
};