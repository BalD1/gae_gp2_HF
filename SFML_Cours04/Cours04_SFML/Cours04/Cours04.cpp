#include <iostream>
#include <SFML/Graphics.hpp>

#include "Shape.hpp"
#include "Utility.hpp"

#pragma region Variables

#pragma region Player

sf::CircleShape playerHead;
sf::CircleShape eyeL;
sf::CircleShape eyeR;
sf::RectangleShape playerHP;
sf::RectangleShape canon;

float playerSpeed = 5;
float invincibilityCD = 1;
float inv_Timer = 0;
float fireCD = 0.5f;
float f_Timer = 0;

#pragma endregion

#pragma region Enemy

sf::CircleShape enemy;
sf::RectangleShape enemyHP;
float enemySpeed = 2;

#pragma endregion

sf::Vector2f windowCenter;
sf::Vector2i mousePos;

std::vector<sf::CircleShape> projVec;
int projectilesNum = 10;

bool anyProjectileFired;
bool gameEnd;

#pragma endregion

void ProcessInputs();
void CanonRotation();
void Movements(sf::Vector2f dir);
void Movements(float dirX, float dirY);
void EnemyMovements();
void Fire();
void ProjectilesBehaviour();
void SetProjectile(sf::CircleShape* projectile);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720, 64), "wesh la mif c'est moi la fenetre de ouf");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	windowCenter = sf::Vector2f(window.getSize().x / 3, window.getSize().y / 4);

	gameEnd = false;
	anyProjectileFired = false;
	sf::err().rdbuf(NULL);

#pragma region Player

	playerHead = SetCircle(100, sf::Color::White, windowCenter);
	playerHead.move(100, 100);

	sf::Vector2f playerHPOffset = sf::Vector2f(-25, -50);
	playerHP = SetRectangle(200, 40, sf::Color::Red, playerHead.getPosition() + playerHPOffset);

	inv_Timer = invincibilityCD;

	eyeL = SetCircle(20, sf::Color::Blue, windowCenter);
	eyeL.move(130, 140);
	
	eyeR = SetCircle(20, sf::Color::Blue, windowCenter);
	eyeR.move(220, 140);

	canon = SetRectangle(100, 20, sf::Color::Red, windowCenter);
	canon.move(100, 210);

#pragma endregion

#pragma region  Enemy

	enemy = SetCircle(20, sf::Color::Red, windowCenter);
	enemy.move(500, 200);

	sf::Vector2f enemyHPOffset = sf::Vector2f(-25, -25);
	enemyHP = SetRectangle(100, 20, sf::Color::Red, enemy.getPosition() + enemyHPOffset);
	enemySpeed = 2;

#pragma endregion

	mousePos = sf::Mouse::getPosition(window);

	for (int i = 0; i < projectilesNum; i++)
	{
		sf::CircleShape c(0);
		c = SetCircle(10, sf::Color::Transparent, Vector2zero());
		projVec.push_back(c);
	}

#pragma region Texts

	sf::Font cybrpnukFont;
	if (!cybrpnukFont.loadFromFile("Cybrpnuk2.ttf"));
	{

	}
	sf::Text title = SetText(50, "CYBERPUNK 2077", sf::Color::Yellow, cybrpnukFont);
	title.setFont(cybrpnukFont);

	sf::Text endText = SetText(70, "", sf::Color::Yellow, cybrpnukFont);
	endText.setFont(cybrpnukFont);
	endText.setPosition(sf::Vector2f(windowCenter.x - 200, windowCenter.y + 100));

#pragma endregion

	gameEnd = false;
	anyProjectileFired = false;

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

		if (!gameEnd)
		{
			mousePos = sf::Mouse::getPosition(window);

			CanonRotation();

			EnemyMovements();

			enemyHP.setPosition(enemy.getPosition() + enemyHPOffset);
			playerHP.setPosition(playerHead.getPosition() + playerHPOffset);

			ProcessInputs();
			if (anyProjectileFired)
				ProjectilesBehaviour();

			if (f_Timer > 0)
				f_Timer -= elapsed.asSeconds();
			if (inv_Timer > 0)
			{
				inv_Timer -= elapsed.asSeconds();
			}
			else
			{
				if (enemy.getGlobalBounds().intersects(playerHead.getGlobalBounds()))
				{
					inv_Timer = invincibilityCD;
					playerHP.setScale(playerHP.getScale().x - 0.2f, 1);

					if (playerHP.getScale().x <= 0.01f)
					{
						playerHead.setFillColor(sf::Color::Transparent);
						canon.setFillColor(sf::Color::Transparent);
						eyeL.setFillColor(sf::Color::Transparent);
						eyeR.setFillColor(sf::Color::Transparent);
						gameEnd = true;
					}
				}
			}
		}
		else
		{
			if (enemy.getFillColor() == sf::Color::Transparent)
				endText.setString("LOL YOU WIN GG LE REUF");
			else if (playerHead.getFillColor() == sf::Color::Transparent)
				endText.setString("PTDR YOU LOSE LE NULOS");
		}


		window.clear();

#pragma region Draws

		window.draw(playerHead);
		window.draw(eyeL);
		window.draw(eyeR);
		window.draw(playerHP);
		window.draw(enemy);
		window.draw(enemyHP);
		for (int i = 0; i < projectilesNum; i++)
		{
			window.draw(projVec[i]);
		}
		window.draw(canon);
		window.draw(title);

		if (gameEnd)
			window.draw(endText);

#pragma endregion

		window.display();
	}

}


void ProcessInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		Movements(-1, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		Movements(1, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		Movements(0, -1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		Movements(0, 1);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button(0)))
	{
		if (f_Timer <= 0)
			Fire();
	}
}
void CanonRotation()
{		sf::Vector2f offset = canon.getPosition();
		offset.x -= mousePos.x;
		offset.y -= mousePos.y;

		float angle = atan2(-offset.y, -offset.x) * (360 / (3.14 * 2));
		canon.setRotation(angle);
}
void Movements(sf::Vector2f dir)
{
	sf::Vector2f movement = MultVectors(dir, playerSpeed);
	playerHead.move(movement);
	canon.move(movement);
	eyeL.move(movement);
	eyeR.move(movement);
}
void Movements(float dirX, float dirY)
{
	sf::Vector2f movement = MultVectors(sf::Vector2f(dirX, dirY), playerSpeed);
	playerHead.move(movement);
	canon.move(movement);
	eyeL.move(movement);
	eyeR.move(movement);
}

void EnemyMovements()
{
	sf::Vector2f difference = (playerHead.getPosition() - enemy.getPosition());

	float length = sqrt((difference.x * difference.x) + (difference.y * difference.y));
	sf::Vector2f direction = DivVectors(difference, length);

	enemy.move(direction.x * enemySpeed, direction.y * enemySpeed);
}

void Fire()
{
	f_Timer = fireCD;

	if (anyProjectileFired)
	{
		for (int i = 0; i < projectilesNum; i++)
		{
			if (projVec[i].getFillColor() == sf::Color::Transparent)
			{
				SetProjectile(&projVec[i]);
				return;
			}
		}

		sf::CircleShape newProj(0);
		newProj = SetCircle(10, sf::Color::Transparent, Vector2zero());
		SetProjectile(&newProj);
		projVec.push_back(newProj);
		projectilesNum += 1;
	}
	else
	{
		SetProjectile(&projVec[0]);
		anyProjectileFired = true;
	}
}

void ProjectilesBehaviour()
{
	for (int i = 0; i < projectilesNum; i++)
	{
		if (projVec[i].getFillColor() != sf::Color::Transparent)
		{
			float projRad = 3.14 / 180 * projVec[i].getRotation();
			float x = 10.0f * cos(projRad);
			float y = 10.0f * sin(projRad);
			projVec[i].move(x, y);

			if (projVec[i].getGlobalBounds().intersects(enemy.getGlobalBounds()))
			{
				if (enemyHP.getScale().x == 1)
					enemyHP.setScale(sf::Vector2f(0.5f, 1));
				else
				{
					enemy.setFillColor(sf::Color::Transparent);
					enemyHP.setFillColor(sf::Color::Transparent);
					gameEnd = true;
				}

				projVec[i].setFillColor(sf::Color::Transparent);
			}
			sf::Vector2f projPos = projVec[i].getPosition();
			if (projPos.x < 0 || projPos.x > 1280 ||
				projPos.y < 0 || projPos.y > 720)
			{
				projVec[i].setFillColor(sf::Color::Transparent);
			}
		}
	}

}

void SetProjectile(sf::CircleShape *projectile)
{
	projectile->setFillColor(sf::Color::Green);
	projectile->setRotation(canon.getRotation());
	projectile->setPosition(canon.getPosition());
}
