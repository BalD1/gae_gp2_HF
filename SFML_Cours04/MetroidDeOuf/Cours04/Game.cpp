#include "stdafx.hpp"
#include "Game.hpp"

#pragma region Initiations

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1280, 960), "MetroidDeOuf", sf::Style::Close | sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);
	this->window.setFramerateLimit(60);

	ImGui::SFML::Init(this->window);

	windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	windowCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

}

void Game::closeWindow()
{
	this->window.close();
}

void Game::initMusic()
{
	audioManager.setMusic("Assets/Sounds/music.ogg");
}

void Game::initPlayer()
{
	this->player = new Player("Samus", 7,7, stride);
	this->player->setWorld(world);
	this->player->setGravity(gravity);
}

void Game::initWorld()
{
	this->world = new World();
	world->gravity = this->gravity;
	int floor = 24;
	for (int i = 0; i < 20; i++)
		this->world->placeWall(i, floor);

}

void Game::initEnemies()
{
	textures[0] = new sf::Texture();
	if (!textures[0]->loadFromFile("Assets/Graphs/red.png"))
		printf("red texture could not be loaded in Assets/Graphs/red.png");
	textures[1] = new sf::Texture();
	if (!textures[1]->loadFromFile("Assets/Graphs/purple.png"))
		printf("purple texture could not be loaded in Assets/Graphs/purple.png");
	for (int i = 1; i < 6; i++)
	{
		char c[50];
		sprintf_s(c, "e%d", i);
		Character* e = new Character(c, i, 5, stride);
		e->setTexture(textures[0]);
		e->setWorld(world);
		e->setGravity(gravity);
		charactersList.push_back(e);
	}
}

void Game::initGrid()
{
	gridRct = sf::RectangleShape(sf::Vector2f(stride, stride));
	gridRct.setOutlineColor(sf::Color::White);
	gridRct.setOutlineThickness(0.9f);
	gridRct.setFillColor(sf::Color::Transparent);
}

#pragma endregion

Game::Game()
{
	this->initWindow();
	this->initWorld();
	this->initPlayer();
	this->initEnemies();
	this->initMusic();
	this->initGrid();

	mouseShape = SetCircle(3, sf::Color::Magenta, vectoriToVectorf(sf::Mouse::getPosition(window)));

	world->worldInitialized = true;
	//tmp
	sf::err().rdbuf(NULL);

}

Game::~Game()
{
}

void Game::update()
{
	mouseShape.setPosition(vectoriToVectorf(sf::Mouse::getPosition(window)));
	//dt
	elapsedTime = clock.restart();
	dt = elapsedTime.asSeconds();

	//updates
	if (world->worldInitialized)
	{
		player->update(dt);
		for (Character* c : charactersList)
			c->update(dt);
	}

	//events
	while (this->window.pollEvent(this->gameEvent))
	{
		ImGui::SFML::ProcessEvent(this->gameEvent);
		switch (gameEvent.type)
		{
			case sf::Event::Closed:
				closeWindow();
				break;
			case sf::Event::KeyPressed:
				checkPressedKey(this->gameEvent.key.code);
				break;
			case sf::Event::KeyReleased:
				checkReleasedKey(this->gameEvent.key.code);
				break;

			case sf::Event::MouseButtonPressed:
				checkPressedMouse(gameEvent.key.code);
				break;

		}
	}

	//ImGui
	this->processImGui();
}

void Game::checkPressedKey(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Escape:
			closeWindow();
			break;
		case sf::Keyboard::Space:
			player->manageEventInputs(key);
			break;

		default:
			break;
	}
}

void Game::checkReleasedKey(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Escape:
			closeWindow();
			break;
		case sf::Keyboard::Space:
			player->manageEventInputsRelease(key);
			break;
	}
}

void Game::checkPressedMouse(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Mouse::Left:
			if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				world->placeWall(mousePosition.x / stride, mousePosition.y / stride);
			}
		break;
	}
}

void Game::processImGui()
{
	bool toolActive;
	ImGui::SFML::Update(window, elapsedTime);

	ImGui::Begin("Tools", &toolActive, ImGuiWindowFlags_MenuBar);

	if (imIdx == 0)
	{
		ImGui::Value("FPS ", 1.0f / dt);
		ImGui::Checkbox("Debug mouse", &debugMouse);
		if (debugMouse)
		{
			ImGui::Text("Mouse : { x%d y%d }", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			ImGui::Text("Mouse cell : { dx%d dy%d }", sf::Mouse::getPosition(window).x / stride, sf::Mouse::getPosition(window).y / stride);
			float rad = mouseShape.getRadius();
			if (ImGui::SliderFloat("Shape size", &rad, 1, 10))
				mouseShape.setRadius(rad);
		}
		if (ImGui::DragFloat("Gravity", &gravity, 0.05f, -5, 5))
		{
			world->gravity = this->gravity;
		}

		float vol = audioManager.musicVolume;
		if (ImGui::DragFloat("Volume", &vol, 1, 0, 100))
		{
			audioManager.changeMusicVolume(vol);

		}
		ImGui::Checkbox("Draw grid", &renderGrid);
		if (renderGrid)
		{
			ImGui::DragFloat("Grid X", &gridSize.x, 1, 0);
			ImGui::DragFloat("Grid Y", &gridSize.y, 1, 0);
		}
	}
	else if (imIdx == 1)
	{
		if (ImGui::TreeNode("Existing characters"))
		{
			int idx = 0;

			charactersImGui((Character*)player, idx, true);

			for (Character* c : charactersList)
			{
				ImGui::PushID(idx);

				charactersImGui(c, idx);

				idx++;
				ImGui::PopID();
			}

			ImGui::Spacing();

			if (ImGui::TreeNode("Create new"))
			{
				static char name[20] = "";
				ImGui::InputText("Name", name, 20);
				static int pos[2] = { 1,1 };
				ImGui::DragInt2("Pos", pos, 1, 0, 100);
				static int health = 5;
				ImGui::DragInt("Health", &health, 1, 0, 100);
				static int selectedIdx = 0;
				static sf::Texture* selectedTexture = textures[selectedIdx];
				if (ImGui::Combo("Textures", &selectedIdx, texturesNames, IM_ARRAYSIZE(texturesNames)))
				{
					selectedTexture = textures[selectedIdx];
				}
				if (ImGui::Button("+"))
				{
					Character* c = new Character(name, pos[0], pos[1], stride);
					if (health > 0)
						c->currentHealth = c->maxHealth = health;
					c->setTexture(selectedTexture);
					c->setWorld(world);
					c->setGravity(gravity);
					charactersList.push_back(c);
				}
				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
	}


	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::TreeNode("Map"))
			{

				if (ImGui::Button("Save"))
				{
					this->world->saveMapInFile("Assets/Data/map.txt");
				}
				ImGui::Spacing();
				if (ImGui::Button("Load"))
				{
					this->world->loadMap("Assets/Data/map.txt");
				}
				ImGui::Spacing();
				if (ImGui::TreeNode("Erase"))
				{
					if (ImGui::Button("Really ?"))
					{
						this->world->eraseMap();
					}
					ImGui::TreePop();
				}
				ImGui::Spacing();
				ImGui::TreePop();
			}


			ImGui::EndMenu();
		}
		if (ImGui::Button("General"))
			imIdx = 0;
		if (ImGui::Button("Characters"))
			imIdx = 1;
		ImGui::EndMenuBar();
	}

	ImGui::End();
}
void Game::charactersImGui(Character* chara, int idx, bool isPlayer)
{
	static float d;

	if (ImGui::TreeNode(chara->name.c_str()))
	{
		ImGui::Text("Health : %f / %f", chara->currentHealth, chara->maxHealth);

		if (ImGui::Button("Damage"))
		{
			if (isPlayer)
				player->takeDamages(d);
			else
			{
				chara->takeDamages(d);
				if (chara->currentHealth <= 0)
					charactersList.erase(charactersList.begin() + idx);
			}

		}
		ImGui::SameLine();
		if (ImGui::Button("Heal"))
			if (isPlayer)
				player->heal(d);
			else
				chara->heal(d);

		ImGui::SameLine();
		ImGui::DragFloat("amount", &d, 0.5f, 0, 10);
		ImGui::Value("State", (Character::State)chara->characterState);
		if (ImGui::TreeNode("Position"))
		{
			ImGui::Text("Pos : {x%d y%d}", chara->cx, chara->cy);
			ImGui::Text("Mov : {x%.1f y%.1f}", chara->dx, chara->dy);
			chara->moved |= (ImGui::DragInt("cx", &chara->cx, 1));
			chara->moved |= (ImGui::DragInt("cy", &chara->cy, 1));
			chara->moved |= (ImGui::DragFloat("rx", &chara->rx, 0.05f));
			chara->moved |= (ImGui::DragFloat("ry", &chara->ry, 0.05f));

			ImGui::TreePop();
		}
		ImGui::Separator();

		ImGui::TreePop();
	}
}

void Game::drawGrid()
{
	for (int y = 0; y < gridSize.y * stride; y += stride) 
	{
		for (int x = 0; x < gridSize.x * stride; x += stride) 
		{
			gridRct.setPosition(x + stride, y + stride);
			window.draw(gridRct);
		}
	}
}

void Game::render()
{
	this->window.clear();

	if (debugMouse)
		window.draw(mouseShape);

	this->world->render(this->window);
	for (Character* c : charactersList)
		c->render(this->window);
	this->player->render(this->window);

	if (renderGrid)
		drawGrid();

	ImGui::SFML::Render(window);

	this->window.display();
}

float Game::deltaTime()
{
	return this->dt;
}



World* Game::getWorld()
{
	return this->world;
}

sf::RenderWindow& Game::getWindow()
{
	return this->window;
}