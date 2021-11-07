#pragma once

#include <SFML/Graphics.hpp>

sf::Vector2f Vector2zero()
{
	sf::Vector2f v = sf::Vector2f(0, 0);
	return v;
}

sf::Vector2f AddVectors(sf::Vector2f a, sf::Vector2f b)
{
	a.x += b.x;
	a.y += b.y;

	return a;
}
sf::Vector2f AddVectors(sf::Vector2f a, float b)
{
	a.x += b;
	a.y += b;

	return a;
}

sf::Vector2f SubVectors(sf::Vector2f a, sf::Vector2f b)
{
	a.x -= b.x;
	a.y -= b.y;

	return a;
}
sf::Vector2f SubVectors(sf::Vector2f a, float b)
{
	a.x -= b;
	a.y -= b;

	return a;
}

sf::Vector2f MultVectors(sf::Vector2f a, sf::Vector2f b)
{
	a.x *= b.x;
	a.y *= b.y;

	return a;
}
sf::Vector2f MultVectors(sf::Vector2f a, float b)
{
	a.x *= b;
	a.y *= b;

	return a;
}

sf::Vector2f DivVectors(sf::Vector2f a, sf::Vector2f b)
{
	a.x /= b.x;
	a.y /= b.y;

	return a;
}
sf::Vector2f DivVectors(sf::Vector2f a, float b)
{
	a.x /= b;
	a.y /= b;

	return a;
}