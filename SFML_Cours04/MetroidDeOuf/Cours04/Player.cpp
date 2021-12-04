#include "stdafx.hpp"
#include "Player.hpp"

Player::Player( std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride) :
	Entity(_name, _speed, _invicibilityCD, _maxHealth, _cx, _cy, _stride)
{
	this->texture = new sf::Texture();
	if (!texture->loadFromFile("Assets/Graphs/samus.png"))
		printf("Samus texture could not be loaded in Assets/Graphs/samus.png");

	this->spr = new sf::Sprite();
	this->spr->setTexture(*texture);
	syncSprite();
}

Player::~Player()
{
}

void Player::im()
{
	moved |= (ImGui::DragInt("cx", &cx, 1));
	moved |= (ImGui::DragInt("cy", &cy, 1));
	moved |= (ImGui::DragFloat("rx", &rx, 0.05f));
	moved |= (ImGui::DragFloat("ry", &ry, 0.05f));
	ImGui::DragFloat("Speed", &speed, 0.005f, 0, 1);
	ImGui::Dummy(ImVec2(40, 0));
	ImGui::SameLine();
	if (ImGui::Button("Step up"))
	{
		moved = true;
		dy = -speed;
	}
	if (ImGui::Button("Step left"))
	{
		moved = true;
		dx = -speed;
	}
	ImGui::SameLine();
	if (ImGui::Button("Step right"))
	{
		moved = true;
		dx = speed;
	}
	ImGui::Dummy(ImVec2(35, 0));
	ImGui::SameLine();
	if (ImGui::Button("Step down"))
	{
		moved = true;
		dy = speed;
	}

	ImGui::Value("dx", (float)dx);
	ImGui::Value("dy", (float)dy);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(*spr);
	ImGui::Begin("Player tools");
	im();
	ImGui::End();
	ImGui::SFML::Render(target);
}
