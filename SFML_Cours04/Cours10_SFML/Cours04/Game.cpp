#include "stdafx.hpp"
#include "Game.hpp"

#pragma region Initiations

void Game::initWindow()
{
	mainView = new sf::View(sf::FloatRect(0, 0, WIDTH, HEIGHT));
	this->window.create(sf::VideoMode(WIDTH, HEIGHT), "MetroidDeOuf", sf::Style::Close | sf::Style::Titlebar);
	this->window.setView(*mainView);
	window.setVerticalSyncEnabled(true);
	this->window.setFramerateLimit(60);

	ImGui::SFML::Init(this->window);

	windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	windowCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
	m_shader = new MainShader();

}

void Game::closeWindow()
{
	this->window.close();
}

void Game::initPlayer()
{
	this->player = new Player("Samus", 8,1, stride);
	this->player->setWorld(world);
	this->player->setGame(this);
	this->player->setGravity(gravity);
}

void Game::initWorld()
{
	this->world = new World();
	world->gravity = this->gravity;
	world->loadMap("Assets/Data/map.txt");
}

void Game::initEnemies()
{
	textures[0] = new sf::Texture();
	if (!textures[0]->loadFromFile("Assets/Graphs/red.png"))
		printf("red texture could not be loaded in Assets/Graphs/red.png");
	textures[1] = new sf::Texture();
	if (!textures[1]->loadFromFile("Assets/Graphs/purple.png"))
		printf("purple texture could not be loaded in Assets/Graphs/purple.png");
}

void Game::initFonts()
{
	titleFont = sf::Font();
	if (!titleFont.loadFromFile("Assets/Fonts/titlefont.ttf"))
		printf("Couldn't load Assets/Fonts/titlefont.ttf");
	baseFont = sf::Font();
	if (!baseFont.loadFromFile("Assets/Fonts/basefont.ttf"))
		printf("Couldn't load Assets/Fonts/basefont.ttf");
}

void Game::initGrid()
{
	gridRct = sf::RectangleShape(sf::Vector2f(stride, stride));
	gridRct.setOutlineColor(sf::Color::White);
	gridRct.setOutlineThickness(0.9f);
	gridRct.setFillColor(sf::Color::Transparent);
}

void Game::processShaders()
{
}

#pragma endregion

Game::Game()
{
	this->initWindow();
	this->initFonts();
	this->initWorld();
	this->initPlayer();
	this->initEnemies();
	this->initGrid();

	mouseShape = SetCircle(3, sf::Color::Magenta, getMousePosition());

	world->worldInitialized = true;
	//tmp
	sf::err().rdbuf(NULL);

}

Game::~Game()
{
}

void Game::update()
{
	mouseShape.setPosition(getMousePosition());
	//dt
	elapsedTime = clock.restart();
	dt = elapsedTime.asSeconds();

	//updates
	if (world->worldInitialized)
	{
		player->update(dt);
	}

	m_shader->playerPos = { this->player->xx, this->player->yy };
	m_shader->update(dt);

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
		case sf::Keyboard::Return:
			World::dij.compute(sf::Vector2i(player->cx, player->cy));
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
				if (strcmp(selectedEntity, "wall") == 0)
				{
					sf::Vector2f mousePosition = getMousePosition();
					world->placeWall(mousePosition.x / stride, mousePosition.y / stride);
				}
				else if (strcmp(selectedEntity, "deathZone") == 0)
				{
					sf::Vector2f mousePosition = getMousePosition();
				}
			}
		break;
		case sf::Mouse::Right:
			sf::Vector2f m = getMousePosition();

			auto& p = World::currentPath;
			World::currentPath.clear();

			sf::Vector2i start = sf::Vector2i(player->cx, player->cy);
			sf::Vector2i end = sf::Vector2i(m.x, m.y);

			sf::Vector2i cur = end;
			World::currentPath.push_back(end);
			while (cur != start)
			{
				auto pos = World::dij.pr.find(cur);
				if (pos != World::dij.pr.end())
				{
					cur = World::dij.pr[cur];
					World::currentPath.push_back(cur);
				}
				else
				{
					World::currentPath.clear();
					break;
				}
			}
			std::reverse(p.begin(), p.end());

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
			sf::Vector2f mousePos = getMousePosition();
			ImGui::Text("Mouse : { x%0.0f y%0.0f }", mousePos.x, mousePos.y);
			ImGui::Text("Mouse cell : { x%0.0f y%0.0f }", mousePos.x / stride, mousePos.y / stride);
			float rad = mouseShape.getRadius();
			if (ImGui::SliderFloat("Shape size", &rad, 1, 10))
				mouseShape.setRadius(rad);
		}
		if (ImGui::DragFloat("Gravity", &gravity, 0.05f, -5, 5))
		{
			world->gravity = this->gravity;
		}
	}
	else if (imIdx == 1)
	{
		static int entityIdx = 0;
		if (ImGui::Combo("Place Entity", &entityIdx, entities, IM_ARRAYSIZE(entities)))
		{
			selectedEntity = entities[entityIdx];
		}
		ImGui::Checkbox("Draw grid", &renderGrid);
		if (renderGrid)
		{
			ImGui::DragFloat("Grid X", &gridSize.x, 1, 0);
			ImGui::DragFloat("Grid Y", &gridSize.y, 1, 0);
		}
		ImGui::Checkbox("Show Death Zones", &world->renderDeathZones);
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
				ImGui::Spacing();
				ImGui::TreePop();
			}


			ImGui::EndMenu();
		}
		if (ImGui::Button("General"))
			imIdx = 0;
		if (ImGui::Button("Characters"))
			imIdx = 1;
		if (ImGui::Button("Map"))
			imIdx = 2;
		ImGui::EndMenuBar();
	}

	ImGui::End();
	m_shader->im();
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
					enemiesList.erase(enemiesList.begin() + idx);
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

void Game::moveCamera(float x, float y)
{
	this->mainView->setCenter(x, y);
	this->window.setView(*mainView);
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

	this->player->render(this->window);
	this->m_shader->render(this->window);

	if (renderGrid)
		drawGrid();


	this->window.draw(stateText);

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

sf::Vector2f Game::getMousePosition()
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(this->window), *mainView);
}

void Game::setGameState(GameState _GS)
{
	this->GS = _GS;
	switch (GS)
	{
	case Game::MainMenu:
		break;

	case Game::InGame:
		stateText.setFillColor(sf::Color::Transparent);
		break;

	case Game::Pause:
		break;

	case Game::GameOver:
		stateText.setFont(baseFont);
		stateText.setPosition(windowCenter.x - 100, 100);
		stateText.setCharacterSize(100);
		stateText.setFillColor(sf::Color::Yellow);
		stateText.setString("Vous mort");
		break;

	case Game::Win:
		break;

	case Game::Cinematic:
		break;

	default:
		break;
	}
}