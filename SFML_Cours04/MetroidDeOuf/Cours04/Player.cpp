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
	syncSprite(1);
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
	ImGui::DragFloat("Speed", &speed, 1, 0, 100);
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
	ImGui::SameLine();
	ImGui::Value("dy", (float)dy);
	ImGui::SameLine();
	ImGui::Checkbox("Fly", &ignoreGravity);
	ImGui::Value("Jump Timer", (float)jumpTimer);
	ImGui::Value("Is Grounded", (bool)isGrounded);
	ImGui::Value("State", (State)characterState);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(*spr);
	ImGui::Begin("Player tools");
	im();
	ImGui::End();
	ImGui::SFML::Render(target);
}

void Player::update(float dt)
{
	this->dt = dt;
	manageInputs();
	Entity::update(dt);

}

void Player::manageInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		dx = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dx = speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		if (characterState != State::Falling)
			jump();
		
}

void Player::manageEventInputs(sf::Keyboard::Key key)
{
	switch (key)
	{
		default:
			break;
	}
}

void Player::manageEventInputsRelease(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Space:
			characterState = State::Falling;
			break;
		default:
			break;
	}
}

void Player::jump()
{
	if (ignoreGravity)
	{
		dy = jumpForce;
		return;
	}
	if (isGrounded && characterState != State::Jumping)
	{
		characterState = State::Jumping;
		jumpTimer = jumpLength;
		dy = jumpForce;
	}
	if (characterState == State::Jumping)
	{
		if (jumpTimer > 0.01f)
		{
			dy = jumpForce;
			jumpTimer -= dt;
		}
		else
		{
			characterState = State::Falling;
			jumpTimer = 0;
		}
	}
}
