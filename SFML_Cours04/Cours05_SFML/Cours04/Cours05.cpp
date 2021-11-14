#include <iostream>
#include <SFML/Graphics.hpp>

#include "Shape.hpp"
#include "Utility.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Weapon.hpp"
#include "Projectile.hpp"

#pragma region Variables

#pragma region Player

Player* _player;
Weapon* _gun;

#pragma endregion

sf::Vector2f windowCenter;
sf::Vector2f windowSize;
sf::Vector2i mousePos;

bool gameEnd;

#pragma endregion

void ProcessInputs(sf::RenderWindow& window);
void DrawGround(sf::RenderWindow& window);
void DrawMountain(sf::RenderWindow& window);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720, 64), "wesh la mif c'est moi la fenetre de ouf");

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	windowCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

	gameEnd = false;

	Projectile projectiles;

	sf::err().rdbuf(NULL);

#pragma region Player

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("Assets/player.png"))
	{
		std::cout << "Could not load player texture";
		return 0;
	}

	Player player = Player(playerTexture, Vector2zero());
	_player = &player;
	_player->setPosition(windowCenter.x, 580);
	_player->setSpeed(3);
		
	sf::Texture gunTexture;	
	if (!gunTexture.loadFromFile("Assets/gun.png"))
	{
		std::cout << "Could not load gun texture";
		return 0;
	}

	Weapon gun = Weapon(gunTexture, 1, 10, player.getPosition(), *_player);
	_gun = &gun;
	_gun->setOffset(50, 20);



#pragma endregion

	mousePos = sf::Mouse::getPosition(window);

#pragma region Texts

	sf::Font cybrpnukFont;
	if (!cybrpnukFont.loadFromFile("Cybrpnuk2.ttf"));
	{

	}
	sf::Text title = SetText(50, "CYBERPUNK 2077", sf::Color::Yellow, cybrpnukFont);
	//title.setFont(cybrpnukFont);

	sf::Text endText = SetText(70, "", sf::Color::Yellow, cybrpnukFont);
	endText.setFont(cybrpnukFont);
	endText.setPosition(sf::Vector2f(windowCenter.x - 200, windowCenter.y + 100));

#pragma endregion

	gameEnd = false;

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
			_gun->lookAt(mousePos.x, mousePos.y);
			ProcessInputs(window);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && projectiles.projectilesNumber <= 0)
			{
				sf::Vector2f aimDir = (sf::Vector2f)mousePos;
				aimDir.x -= _gun->getPosition().x;
				aimDir.y -= _gun->getPosition().y;

				_gun->fire(&projectiles, NormalizeVector(aimDir));
			}
		}

		_player->update(elapsed.asSeconds());
		_gun->update(elapsed.asSeconds());
		projectiles.update(elapsed.asSeconds());

		window.clear();

#pragma region Draws

		DrawGround(window);
		DrawMountain(window);

		_player->render(window, true);
		_gun->render(window, true);
		projectiles.render(window, true);
		//window.draw(title);

		if (gameEnd)
			window.draw(endText);

#pragma endregion

		window.display();
	}

}

void ProcessInputs(sf::RenderWindow& window)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		_player->move(-1, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		_player->move(1, 0);

}
//sf::Vector2f movement = MultVectors(dir, playerSpeed);

/*
void Fire(sf::RenderWindow& window)
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


// refaire projectiles
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


			sf::Vector2f projPos = projVec[i].getPosition();
			if (projPos.x < 0 || projPos.x > 1280)
			{

			}
			if (projPos.y < 0 || projPos.y > 720)
			{
				
				float rot = projVec[i].getRotation();
				projVec[i].setRotation(rot * -1);
				
			}
		}
	}

}

void SetProjectile(sf::CircleShape* projectile)
{
	projectile->setFillColor(sf::Color::Green);
	projectile->setRotation(canon.getRotation());
	projectile->setPosition(canon.getPosition());
}
*/

void DrawGround(sf::RenderWindow& window)
{
	sf::VertexArray vArr = sf::VertexArray(sf::LinesStrip);

	sf::Color groundColor = sf::Color(sf::Uint8(145), sf::Uint8(145), sf::Uint8(0));
	float baseLine = 600 + 32;

	sf::Vector2f a(0, baseLine);
	sf::Vector2f b(windowSize.x, baseLine);

	vArr.append(sf::Vertex(a, groundColor));
	vArr.append(sf::Vertex(b, groundColor));

	window.draw(vArr);
}

void DrawMountain(sf::RenderWindow& window)
{
	sf::VertexArray vArr = sf::VertexArray(sf::LinesStrip);

	sf::Color mountainColor = sf::Color(sf::Uint8(200), sf::Uint8(99), sf::Uint8(70));
	float baseLine = 610 - 32;

	sf::Vector2f a(0, baseLine);
	sf::Vector2f b(400, baseLine - 330);
	sf::Vector2f c(800, baseLine - 400);
	sf::Vector2f d(windowSize.x, baseLine);

	for (int i = 0; i < 256; i++)
	{
		float t = 1.0f * i / 256;
		float x = catmul(a.x, a.x, b.x, c.x, t);
		float y = catmul(a.y, a.y, b.y, c.y, t);

		vArr.append(sf::Vertex(sf::Vector2f(x, y), mountainColor));
	}
	for (int i = 0; i < 256; i++)
	{
		float t = 1.0f * i / 256;
		float x = catmul(a.x, b.x, c.x, d.x, t);
		float y = catmul(a.y, b.y, c.y, d.y, t);

		vArr.append(sf::Vertex(sf::Vector2f(x, y), mountainColor));
	}
	for (int i = 0; i < 256; i++)
	{
		float t = 1.0f * i / 256;
		float x = catmul(b.x, c.x, d.x, d.x, t);
		float y = catmul(b.y, c.y, d.y, d.y, t);

		vArr.append(sf::Vertex(sf::Vector2f(x, y), mountainColor));
	}
	window.draw(vArr);
}
