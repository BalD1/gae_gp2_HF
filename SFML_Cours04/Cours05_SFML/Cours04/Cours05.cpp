#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Shape.hpp"
#include "Utility.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Weapon.hpp"
#include "Projectile.hpp"
#include "Brick.hpp"
#include "World.hpp"

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

#pragma region Set window

	sf::RenderWindow window(sf::VideoMode(1280, 720, 64), "wesh la mif c'est moi la fenetre de ouf");

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	windowCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

	float dt = 0;

#pragma endregion

	gameEnd = false;

	sf::Music music;
	if (!music.openFromFile("Assets/Sounds/music.ogg"))
	{
		std::cout << "Could not load main music";
		return 0;
	}
	music.setVolume(20);
	music.setLoop(true);
	music.play();
	

	
	sf::SoundBuffer explosion;
	if (!explosion.loadFromFile("Assets/Sounds/explosion.wav"))
	{
		std::cout << "Could not load explosion sound";
		return 0;
	}
	sf::Sound explosionSound;
	explosionSound.setBuffer(explosion);

	sf::Texture brickTexture;
	if (!brickTexture.loadFromFile("Assets/brick.png"))
	{
		std::cout << "Could not load brick texture";
		return 0;
	}

	const int brickLength = 80;
	const int brickRows = brickLength / 15;
	int idx = 0;

	Brick* bricks[brickLength];
	for (int i = 0; i < brickLength / brickRows; i++)
	{
		for (int j = 0; j < brickRows; j++)
		{
			Brick* b = new Brick(brickTexture, 70 * i + 100, 100 + j * 100);
			bricks[idx] = b;
			idx += 1;
		}
	}

	sf::err().rdbuf(NULL);

#pragma region Player

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("Assets/playerpad.png"))
	{
		std::cout << "Could not load player texture";
		return 0;
	}

	Player player = Player(playerTexture, Vector2zero(), true);
	_player = &player;
	_player->setPosition(windowCenter.x, 605);
	_player->setSpeed(10);
		
	sf::Texture gunTexture;	
	if (!gunTexture.loadFromFile("Assets/gun.png"))
	{
		std::cout << "Could not load gun texture";
		return 0;
	}

	Weapon gun = Weapon(gunTexture, 1, 10, player.getPosition(), *_player);
	_gun = &gun;
	_gun->setOffset(75, 20);

	sf::Texture projectileTexture;
	if (!projectileTexture.loadFromFile("Assets/bullet.png"))
	{
		std::cout << "Could not load projectile texture";
	}
	Projectile* ball = new Projectile(*_player, projectileTexture, _gun->getPosition(), sf::Vector2f(75,-10), Vector2zero(), 400, 1, false);


#pragma endregion

	mousePos = sf::Mouse::getPosition(window);

#pragma region Texts

	sf::Font cybrpnukFont;
	if (!cybrpnukFont.loadFromFile("Cybrpnuk2.ttf"));
	{

	}

	int score = 0;
	sf::Text scoreTxt = SetText(50, "score : " + std::to_string(score), sf::Color::Yellow, cybrpnukFont);
	scoreTxt.setFont(cybrpnukFont);
	scoreTxt.setPosition(Vector2zero());

#pragma endregion

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

			if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || (sf::Joystick::getAxisPosition(0, sf::Joystick::Z) > 1)) && !ball->isActive())
			{
				sf::Vector2f aimDir = (sf::Vector2f)mousePos;
				aimDir.x -= _gun->getPosition().x;
				aimDir.y -= _gun->getPosition().y;

				_gun->fire(ball, NormalizeVector(aimDir));
			}
		}

		dt = elapsed.asSeconds();

		_player->update(dt);
		_gun->update(dt);
		ball->update(dt);
		for (int i = 0; i < brickLength; i++)
		{
			if (bricks[i]->alive)
				bricks[i]->update(dt);
		}

		if (ball->isActive())
		{
			for (int i = 0; i < brickLength; i++)
			{
				if (bricks[i]->alive)
				{
					if (bricks[i]->hitbox->intersects(ball->projectileData->spr.getGlobalBounds()))
					{
						ball->bounceX();
						bricks[i]->kill();
						explosionSound.play();
						score += 10;
						scoreTxt.setString("score : " + std::to_string(score));
					}
					else if (bricks[i]->verticalBox->intersects(ball->projectileData->spr.getGlobalBounds()))
					{
						ball->bounceY();
						bricks[i]->kill();
						explosionSound.play();
						score += 10;
						scoreTxt.setString("score : " + std::to_string(score));
					}
					else if (ball->projectileData->hitbox->intersects(_player->spr->getGlobalBounds()) && ball->canBounce)
					{
						ball->canBounce = false;

						ball->projectileData->direction.y *= -1;
					}
				}
			}
		}

		window.clear();

#pragma region Draws

		DrawGround(window);
		DrawMountain(window);

		_player->render(window, false);
		_gun->render(window, false);
		for (int i = 0; i < brickLength; i++)
		{
			if (bricks[i]->alive)
			bricks[i]->render(window, false);
		}

		ball->render(window, false);

		window.draw(scoreTxt);

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

	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100;
	if (x > 0.01 || x < -0.01)
		_player->move(sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100, 0);

	sf::Vector2i rAxis;
	rAxis.x = sf::Joystick::getAxisPosition(0, sf::Joystick::U) / 2;
	rAxis.y = sf::Joystick::getAxisPosition(0, sf::Joystick::V) / 2;
	if (!(rAxis.y > 25 || rAxis.y < 0))
		rAxis.y = 0;

	std::cout << "x : " << rAxis.x << " y : " << rAxis.y << '\n';

	sf::Mouse::setPosition(sf::Mouse::getPosition() + rAxis);
}

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
