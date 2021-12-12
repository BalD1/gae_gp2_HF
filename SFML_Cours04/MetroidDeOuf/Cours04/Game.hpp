#pragma once
#include "stdafx.hpp"
#include "AudioManager.hpp"
#include "Player.hpp"
#include "Character.hpp"
#include "World.hpp"

class Game
{
private:

	// vars

	sf::RenderWindow			window;
	sf::Event					gameEvent;

	sf::RectangleShape			gridRct;
	sf::Vector2f				gridSize = { 25,25 };
	bool						renderGrid = false;

	bool						debugMouse = false;

	sf::CircleShape				mouseShape;

	sf::Clock					clock;
	sf::Time					elapsedTime;
	float						dt = 0;

	AudioManager				audioManager;

	Player*						player;
	sf::Texture*				textures[2];
	const char*					texturesNames[2] = { "redTexture", "purpleTexture"};
	std::vector<Character*>		charactersList;

	World*						world;

	int							imIdx = 0;

	// funcs

	void initWindow();
	void closeWindow();
	void initMusic();
	void initPlayer();
	void initWorld();
	void initEnemies();
	void initGrid();

public:

	// vars

	sf::Vector2f				windowSize;
	sf::Vector2f				windowCenter;

	int							stride = 32;

	float						gravity = 2.47f;

	// funcs

	Game();
	~Game();


	void update();

	// keys managers
	void checkPressedKey(sf::Keyboard::Key key);
	void checkReleasedKey(sf::Keyboard::Key key);
	void checkPressedMouse(sf::Keyboard::Key key);

	// imgui
	void processImGui();
	void charactersImGui(Character* chara, int idx, bool isPlayer = false);

	// renderers
	void drawGrid();
	void render();

	// dt
	float deltaTime();

	// gets
	World* getWorld();
	sf::RenderWindow& getWindow();
};

