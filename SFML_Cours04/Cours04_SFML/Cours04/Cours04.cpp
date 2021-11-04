#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720, 64), "wesh la mif c'est moi la fenetre de ouf");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	sf::CircleShape mouseShape(5);
	mouseShape.setFillColor(sf::Color::Magenta);

	sf::CircleShape enemy(20);
	enemy.setFillColor(sf::Color::Red);	
	enemy.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 4));
	enemy.move(500, 200);


	sf::CircleShape player(100);
	player.setFillColor(sf::Color::White);
	player.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 4));
	player.move(100, 100);	

	sf::CircleShape eyeL(20);
	eyeL.setFillColor(sf::Color::Blue);
	eyeL.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 4));
	eyeL.move(130, 140);
	
	sf::CircleShape eyeR(20);
	eyeR.setFillColor(sf::Color::Blue);
	eyeR.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 4));
	eyeR.move(220, 140);

	sf::RectangleShape canon(sf::Vector2f(100, 20));
	canon.setFillColor(sf::Color::Red);
	canon.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 4));
	canon.move(150, 230);

	sf::RectangleShape canonFirePoint(sf::Vector2f(10,20));
	canonFirePoint.setFillColor(sf::Color::Blue);
	sf::Vector2f firePointOffset = canon.getPosition();
	firePointOffset.x ;
	firePointOffset.y += 90;
	canonFirePoint.setPosition(firePointOffset);


	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	sf::CircleShape projectile(10);
	projectile.setFillColor(sf::Color::Transparent);

	sf::Font font;
	sf::Text title;
	if (!font.loadFromFile("Cybrpnuk2.ttf"));
	{

	}

	title.setFont(font);
	title.setString("CYBERPUNK 2077");
	title.setCharacterSize(50);
	title.setFillColor(sf::Color::Yellow);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		mousePos = sf::Mouse::getPosition(window);
		mouseShape.setPosition(mousePos.x, mousePos.y);

		sf::Vector2f offset = canon.getPosition();
		offset.x -= mousePos.x;
		offset.y -= mousePos.y;

		float angle = atan2(-offset.y, -offset.x) * (360 / (3.14 * 2));
		canon.setRotation(angle);

		firePointOffset = canon.getPosition();
		firePointOffset.x += 90.0f;
		canonFirePoint.setPosition(firePointOffset);
		canonFirePoint.setRotation(angle);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			player.move(sf::Vector2f(-3.0f, 0));
			canon.move(sf::Vector2f(-3.0f, 0));
			eyeR.move(sf::Vector2f(-3.0f, 0));
			eyeL.move(sf::Vector2f(-3.0f, 0));
			canonFirePoint.move(sf::Vector2f(-3.0f, 0));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			player.move(sf::Vector2f(3.0f, 0));
			canon.move(sf::Vector2f(3.0f, 0));
			eyeL.move(sf::Vector2f(3.0f, 0));
			eyeR.move(sf::Vector2f(3.0f, 0));
			canonFirePoint.move(sf::Vector2f(3.0f, 0));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			player.move(sf::Vector2f(0, -3.0f));
			canon.move(sf::Vector2f(0, -3.0f));
			eyeL.move(sf::Vector2f(0, -3.0f));
			eyeR.move(sf::Vector2f(0, -3.0f));
			canonFirePoint.move(sf::Vector2f(0, -3.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			player.move(sf::Vector2f(0., 3.0f));
			canon.move(sf::Vector2f(0., 3.0f));
			eyeL.move(sf::Vector2f(0., 3.0f));
			eyeR.move(sf::Vector2f(0., 3.0f));
			canonFirePoint.move(sf::Vector2f(0., 3.0f));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button(0)))
		{
			projectile.setFillColor(sf::Color::Green);
			projectile.setRotation(canon.getRotation());
			projectile.setPosition(canon.getPosition());
		}

		if (projectile.getFillColor() != sf::Color::Transparent)
		{
			float projRad = 3.14 / 180 * projectile.getRotation();
			float x = 10.0f * cos(projRad);
			float y = 10.0f * sin(projRad);
			projectile.move(x, y);

			if (projectile.getGlobalBounds().intersects(enemy.getGlobalBounds()))
			{
				enemy.setFillColor(sf::Color::Transparent);
				projectile.setFillColor(sf::Color::Transparent);
			}
		}

		window.clear();
		window.draw(player);
		window.draw(eyeL);
		window.draw(eyeR);
		window.draw(enemy);
		window.draw(projectile);
		window.draw(canon);
		window.draw(canonFirePoint);
		window.draw(title);
		window.draw(mouseShape);
		
		window.display();
	}

}
