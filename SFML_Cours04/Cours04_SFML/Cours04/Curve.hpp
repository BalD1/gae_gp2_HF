#pragma once

#include <SFML/Graphics.hpp>

class Curve
{
public:
	std::vector<float> px;
	std::vector<float> py;

	void clear()
	{
		px.clear();
		py.clear();
	}


	void addPoint(sf::Vector2f p)
	{
		px.push_back(p.x);
		py.push_back(p.y);
	}

	void draw(sf::RenderWindow& wnd)
	{
		sf::VertexArray arr;
		arr.setPrimitiveType(sf::PrimitiveType::LineStrip);
		sf::Color c = sf::Color::Red;
		for (int i = 1; i < px.size() - 2; i++)
		{
			int im = i == 0 ? 0 : i;
			int ip1 = (i >= px.size() - 1) ? px.size() - 1 : i;
			int ip2 = (i >= px.size() - 2) ? px.size() - 2 : i;
			sf::Vector2f p0 = sf::Vector2f(px[im], py[im]);
			sf::Vector2f p1 = sf::Vector2f(px[i], py[i]);
			sf::Vector2f p2 = sf::Vector2f(px[ip1], py[ip1]);
			sf::Vector2f p3 = sf::Vector2f(px[ip2], py[ip2]);

			/*
			for (int sub = 0; sub < 16; sub++)
			{
				sf::Vector2f p = 
				{
					Curve::c(p0.x, p1.x, p2.x, p3.x, i / 15),
					Curve::c(p0.y, p1.y, p2.y, p3.y, i / 15)
				}
			arr.append(sf::Vertex(sf::Vector2f(px[i], py[i]), c));
			}
			*/
		}
		wnd.draw(arr);
	}
};