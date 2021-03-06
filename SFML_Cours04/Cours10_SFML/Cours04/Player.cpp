#include "stdafx.hpp"
#include "Player.hpp"
#include "Game.hpp"

Player::Player(std::string _name, float _cx, float _cy, int _stride) :
	Character(_name, _cx, _cy, _stride)
{
	syncTransform();
}

Player::Player( std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride) :
	Character(_name, _speed, _invicibilityCD, _maxHealth, _cx, _cy, _stride)
{
	syncTransform();
}

Player::~Player()
{
}

void Player::setGame(Game* _gameRef)
{
	this->gameRef = _gameRef;
	gameRef->moveCamera(xx, yy);
}

void Player::setWorld(World* _worldRef)
{
	this->worldRef = _worldRef;
}

void Player::im()
{
	ImGui::Text("Position and movements");
	moved |= (ImGui::DragInt("cx", &cx, 1));
	moved |= (ImGui::DragInt("cy", &cy, 1));
	moved |= (ImGui::DragFloat("rx", &rx, 0.05f));
	moved |= (ImGui::DragFloat("ry", &ry, 0.05f));
	ImGui::DragFloat("Speed", &speed, 1, 0, 100);
	ImGui::DragFloat("Jump Force", &jumpForce, 1, 1, 100);
	ImGui::DragFloat("Falling speed factor", &fallingSpeedFactor, 0.5f, 0);
	ImGui::DragFloat("Friction x", &frct_x, 0.05f, 0, 1);
	ImGui::DragFloat("Friction y", &frct_y, 0.05f, 0, 1);
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

	ImGui::Separator();
	ImGui::Text("Health");
	ImGui::Text("HP : %f / %f", currentHealth, maxHealth);
	if (ImGui::Button("Revive"))
	{
		this->currentHealth = this->maxHealth;
		gameRef->setGameState(Game::GameState::InGame);
	}
}

void Player::render(sf::RenderTarget& target)
{
	ImGui::Begin("Player tools");
	im();
	ImGui::End();
	ImGui::SFML::Render(target);

	states.transform = getTransform();
		target.draw(*this->spr, states);

}

void Player::update(float dt)
{
	if (!alive())
		return;

	this->dt = dt;
	manageInputs();
	Character::update(dt);

	if (characterState == State::Jumping)
		jumpBehaviour();

	if (moved)
	{
		gameRef->moveCamera(this->xx, this->yy);
	}
}

void Player::manageInputs()
{
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
			jumpTimer = 0;
			break;
		default:
			break;
	}
}

void Player::jump()
{
	if (ignoreGravity)
	{
		dy = jumpForce * -1;
		return;
	}
	if (isGrounded && characterState != State::Jumping)
	{
		characterState = State::Jumping;
		jumpTimer = jumpLength;
		dy = jumpForce * -1;
	}
}

void Player::jumpBehaviour()
{
	if (jumpTimer > 0.01f)
	{
		dy = jumpForce * -1;
		jumpTimer -= dt;
	}
	else
	{
		characterState = State::Falling;
		jumpTimer = 0;
	}
}

void Player::takeDamages(float rawDamages)
{
	if (invincibility_Timer > 0)
		return;

	invincibility_Timer = invincibility_CD;
	this->currentHealth -= rawDamages;
	if (currentHealth <= 0)
	{
		this->kill();
	}
}

void Player::kill()
{
	this->currentHealth = 0;
	gameRef->setGameState(Game::GameState::GameOver);
}
