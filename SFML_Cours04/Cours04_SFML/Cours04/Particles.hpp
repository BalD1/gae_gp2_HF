#pragma once

#include "SFML/Graphics.hpp"
#include "Shape.hpp"

class Particles
{
public:

	float lifetime = 1;
	float speed = 1;
	int number = 10;
	sf::VertexArray path;
	std::vector<sf::CircleShape> shapes;

	Particles(sf::Vector2f pos, int newNumber = 10 ,float newLifetime = 1, float newSpeed = 1, int size = 10)
	{
		lifetime = newLifetime;
		speed = newSpeed;
		number = newNumber;
		for (int i = 0; i < number; i++)
		{
			sf::CircleShape c = SetCircle(size, sf::Color::Magenta, pos);
			shapes.push_back(c);
		}
		CreatePath();
	}

	void Update(float elapsedTime)
	{
		for (sf::CircleShape& c : shapes)
		{
			sf::Vector2f dir = Vector2zero();

			float s = (speed * elapsedTime) + rand() % 10;
			//c.move(s, 0);
		}
		for (int i = 0; i < number; i++)
		{
			float s = (speed * elapsedTime) + rand() % 10;

			shapes[i].setPosition(shapes[i].getPosition().x + speed, 0);
		}
	}

	void CreatePath()
	{
		path = sf::VertexArray(sf::LinesStrip);
		sf::Vector2f basePos = shapes[0].getPosition();

		sf::Vector2f a(basePos);
		sf::Vector2f b(basePos.x * 2, basePos.y * 2);

		path.append(a);
		path.append(b);
	}

	void DrawParticles(sf::RenderWindow& window)
	{
		for (sf::CircleShape& c : shapes)
		{
			window.draw(c);
		}
	}



private:
};