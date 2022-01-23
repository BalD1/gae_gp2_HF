#pragma once
#include "stdafx.hpp"
#include "SFML/Graphics/Glsl.hpp"
#include "SFML/Graphics/Shader.hpp"
#include "HotReloadShader.hpp"

class MainShader
{
private:

	sf::Sprite*						spr = nullptr;
	sf::Texture*					texture = nullptr;
	sf::RectangleShape*				rect = nullptr;
	sf::Shader*						s_mainShader;

	const char*						vertexPath = "vertex_shader.vert";
	const char*						fragPath = "fragment_shader.frag";

	sf::Glsl::Vec4					colorVec = { 1,1,1,1 };
	float							imColAdd[4] = { 0,0,0,0 };
	float							imColMul[4] = { 1,1,1,1 };
	
	float							imColTransR[4] = { 1,0,0,0 };
	float							imColTransG[4] = { 0,1,0,0 };
	float							imColTransB[4] = { 0,0,1,0 };
	float							imColTransA[4] = { 0,0,0,1 };

	sf::Vector2f					imMovement = { 1,1 };
	sf::Vector2f					dispClamp = { 10,10 };
	sf::Vector2f					imBlur = { 0,0 };
	float							imMovementSpeed = 0;
	float							imDisplacement = 0;
	

	sf::Glsl::Vec4					colAdd = sf::Glsl::Vec4(0,0,0,0);
	sf::Glsl::Vec4					colMul = sf::Glsl::Vec4(1,1,1,1);

	float id[16] = 
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1,
	};

	sf::Glsl::Mat4					colTrans = sf::Glsl::Mat4(id);

	HotReloadShader					s_reload;

public:

	float							sTime = -5;
	float							sTimeRange = 5;
	float							sTimeDirection = 1;
	float							sTimeSpeed = 0;
	sf::Vector2f					playerPos;

	MainShader();
	~MainShader();

	bool loadFromFile(const char* path, std::string& res);

	void im();

	void update(float dt);
	void render(sf::RenderTarget& target);

	void clamp(float& f, float min, float max);
};

