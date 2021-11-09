#pragma once

#include <SFML/Graphics.hpp>

#pragma region Vectors

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

sf::Vector2f NormalizeVector(sf::Vector2f vector)
{

	return vector;
}

sf::Vector2f Reflect(sf::Vector2f a)
{
	return a;
}

#pragma endregion

float catmul(float p0, float p1, float p2, float p3, float t)
{
	float q = p1 * 2.0f;
	float t2 = t * t;

	q += (-p0 + p2) * t;
	q += (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2;
	q += (-p0 + 3.0f * p1 - 3 * p2 + p3) * t2 * t;

	return 0.5 * q;
}