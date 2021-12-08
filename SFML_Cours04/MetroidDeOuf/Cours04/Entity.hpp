#pragma once
#include "stdafx.hpp"
#include "World.hpp"

class Hitbox;

class Entity
{
private: 
	void init();

public:

#pragma region Variables

	sf::Sprite*			spr = nullptr;
	sf::Texture*		texture = nullptr;

	std::string			tag = "";

#pragma region Grid
						// grid coordinates
	int					cx = 0;
	int					cy = 0;
						// ratios of player position inside cells
	float				rx = 0.0f;
	float				ry = 0.0f;

						// coordinates from (cx+rx) : (cy+ry)
	float				xx = 0.0f;
	float				yy = 0.0f;

						// movements
	float				dx = 0.0f;
	float				dy = 0.0f;

	int					stride = 32;

#pragma endregion


#pragma endregion

#pragma region Funcs

	Entity(float _cx, float _cy, int _stride);
	Entity(float _cx, float _cy, int _stride, sf::Texture* _texture);

	~Entity();

	void setTag(const std::string _tag);
	const std::string getTag();

	void syncSprite(float dt);
	void render(sf::RenderTarget& target);

	void update(float dt);


#pragma endregion
};