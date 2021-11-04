#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720, 64), "wesh la mif c'est moi la fenetre de ouf");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	sf::Vector2f windowCenter = sf::Vector2f(window.getSize().x / 3, window.getSize().y / 4);

	sf::CircleShape mouseShape(5);
	mouseShape.setFillColor(sf::Color::Magenta);


	sf::CircleShape enemy(20);
	enemy.setFillColor(sf::Color::Red);	
	enemy.setPosition(windowCenter);
	enemy.move(500, 200);
	sf::RectangleShape enemyHP(sf::Vector2f(100, 20));
	enemyHP.setFillColor(sf::Color::Red);
	sf::Vector2f enemyHPOffset = sf::Vector2f(-25, -25);
	enemyHP.setPosition(enemy.getPosition() + enemyHPOffset);
	float enemySpeed = 2;

	sf::CircleShape player(100);
	player.setFillColor(sf::Color::White);
	player.setPosition(windowCenter);
	player.move(100, 100);
	sf::RectangleShape playerHP(sf::Vector2f(200, 40));
	playerHP.setFillColor(sf::Color::Red);
	sf::Vector2f playerHPOffset = sf::Vector2f(-25, -50);
	playerHP.setPosition(player.getPosition() + playerHPOffset);
	float playerSpeed = 5;
	float invincibilityTime = 1;
	float invincibilityTimer = invincibilityTime;

	sf::CircleShape eyeL(20);
	eyeL.setFillColor(sf::Color::Blue);
	eyeL.setPosition(windowCenter);
	eyeL.move(130, 140);
	
	sf::CircleShape eyeR(20);
	eyeR.setFillColor(sf::Color::Blue);
	eyeR.setPosition(windowCenter);
	eyeR.move(220, 140);

	sf::RectangleShape canon(sf::Vector2f(100, 20));
	canon.setFillColor(sf::Color::Red);
	canon.setPosition(windowCenter);
	canon.move(100, 210);

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

	sf::Text endText;
	endText.setFont(font);
	endText.setCharacterSize(70);
	endText.setFillColor(sf::Color::Yellow);
	endText.setPosition(sf::Vector2f(windowCenter.x - 200, windowCenter.y + 100));
	bool gameEnd = false;

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time elapsed = clock.getElapsedTime();
		clock.restart();

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

		sf::Vector2f difference = (player.getPosition() - enemy.getPosition());

		float length = sqrt((difference.x * difference.x) + (difference.y * difference.y));
		sf::Vector2f direction = sf::Vector2f(difference.x / length, difference.y / length);

		enemy.move(direction.x * enemySpeed, direction.y * enemySpeed);
		enemyHP.setPosition(enemy.getPosition() + enemyHPOffset);
		playerHP.setPosition(player.getPosition() + playerHPOffset);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			player.move(sf::Vector2f(-playerSpeed, 0));
			canon.move(sf::Vector2f(-playerSpeed, 0));
			eyeR.move(sf::Vector2f(-playerSpeed, 0));
			eyeL.move(sf::Vector2f(-playerSpeed, 0));
			canonFirePoint.move(sf::Vector2f(-playerSpeed, 0));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			player.move(sf::Vector2f(playerSpeed, 0));
			canon.move(sf::Vector2f(playerSpeed, 0));
			eyeL.move(sf::Vector2f(playerSpeed, 0));
			eyeR.move(sf::Vector2f(playerSpeed, 0));
			canonFirePoint.move(sf::Vector2f(playerSpeed, 0));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			player.move(sf::Vector2f(0, -playerSpeed));
			canon.move(sf::Vector2f(0, -playerSpeed));
			eyeL.move(sf::Vector2f(0, -playerSpeed));
			eyeR.move(sf::Vector2f(0, -playerSpeed));
			canonFirePoint.move(sf::Vector2f(0, -playerSpeed));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			player.move(sf::Vector2f(0., playerSpeed));
			canon.move(sf::Vector2f(0., playerSpeed));
			eyeL.move(sf::Vector2f(0., playerSpeed));
			eyeR.move(sf::Vector2f(0., playerSpeed));
			canonFirePoint.move(sf::Vector2f(0., playerSpeed));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button(0)))
		{
			projectile.setFillColor(sf::Color::Green);
			projectile.setRotation(canon.getRotation());
			projectile.setPosition(canon.getPosition());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			window.close();

		if (projectile.getFillColor() != sf::Color::Transparent)
		{
			float projRad = 3.14 / 180 * projectile.getRotation();
			float x = 10.0f * cos(projRad);
			float y = 10.0f * sin(projRad);
			projectile.move(x, y);

			if (projectile.getGlobalBounds().intersects(enemy.getGlobalBounds()))
			{
				if (enemyHP.getScale().x == 1)
					enemyHP.setScale(sf::Vector2f(0.5f, 1));
				else
				{
					enemy.setFillColor(sf::Color::Transparent);
					enemyHP.setFillColor(sf::Color::Transparent);
					endText.setString("LOL YOU WIN GG LE REUF");
					gameEnd = true;
				}

				projectile.setFillColor(sf::Color::Transparent);
			}
		}
		if (enemy.getFillColor() != sf::Color::Transparent && player.getFillColor() != sf::Color::Transparent)
		{
			if (invincibilityTimer > 0)
			{
				invincibilityTimer -= elapsed.asSeconds();
			}
			else
			{
				if (enemy.getGlobalBounds().intersects(player.getGlobalBounds()))
				{
					invincibilityTimer = invincibilityTime;
					playerHP.setScale(playerHP.getScale().x - 0.2f, 1);

					if (playerHP.getScale().x <= 0.01f)
					{
						player.setFillColor(sf::Color::Transparent);
						canon.setFillColor(sf::Color::Transparent);
						eyeL.setFillColor(sf::Color::Transparent);
						eyeR.setFillColor(sf::Color::Transparent);
						endText.setString("PTDR YOU LOSE LE NULOS");
						gameEnd = true;
					}
				}
			}
		}

		window.clear();
		window.draw(player);
		window.draw(eyeL);
		window.draw(eyeR);
		window.draw(playerHP);
		window.draw(enemy);
		window.draw(enemyHP);
		window.draw(projectile);
		window.draw(canon);
		window.draw(canonFirePoint);
		window.draw(title);
		window.draw(mouseShape);

		if (gameEnd)
		{
			window.draw(endText);
		}
		
		window.display();
	}

}
