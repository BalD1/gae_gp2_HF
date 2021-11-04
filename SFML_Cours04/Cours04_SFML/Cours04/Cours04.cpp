#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720, 64), "wesh la mif c'est moi la fenetre de ouf");
	window.setFramerateLimit(60);

	sf::RectangleShape canon(sf::Vector2f(100, 20));
	canon.setFillColor(sf::Color::Red);
	canon.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 4));
	canon.move(150, 230);

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	sf::CircleShape projectile(30);
	projectile.setFillColor(sf::Color::Transparent);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		 mousePos = sf::Mouse::getPosition(window);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			canon.move(sf::Vector2f(-3.0f, 0));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			canon.move(sf::Vector2f(3.0f, 0));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			canon.move(sf::Vector2f(0, -3.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			canon.move(sf::Vector2f(0., 3.0f));
		}
		canon.rotate(mousePos.x);

		window.clear();
		window.draw(canon);
		window.display();
	}

}
