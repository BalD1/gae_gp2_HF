#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Shape.hpp"
#include "Utility.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

class Entity
{
private: 

public:

#pragma region Variables

	sf::Shape*			spr = nullptr;

#pragma region Grid

	int					cx = 0;
	int					cy = 0;
	float				rx = 0.0f;
	float				ry = 0.0f;

	float				xx = 0.0f;
	float				yy = 0.0f;

	float				dx = 0.0f;
	float				dy = 0.0f;

	int					stride = 16;

#pragma endregion

	bool				moved = false;

	float				speed = 0.5f;

#pragma endregion

#pragma region Funcs

	Entity();
	~Entity();


	void manageMovements();

	void syncSprite();
	void render(sf::RenderTarget& target);

	void update();
};