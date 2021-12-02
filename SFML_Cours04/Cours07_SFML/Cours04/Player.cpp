#include "Player.hpp"

Player::Player(float _cx, float _cy, int _stride)
{
	sf::RectangleShape* _spr = new sf::RectangleShape(sf::Vector2f(0, 0));
	*_spr = SetRectangleWOutline(sf::Vector2f(12, 28), sf::Color::Red, sf::Vector2f(_cx, _cy), sf::Color::Green, 1);
	_spr->setOrigin(_spr->getSize().x * 0.5f, _spr->getSize().y);

	this->spr = _spr;
	cx = _cx;
	cy = _cy;
	stride = _stride;
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
