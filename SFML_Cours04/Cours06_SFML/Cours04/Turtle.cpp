#include "Turtle.hpp"

Turtle::Turtle(sf::Vector2f pos)
{
	transform = Transform();
	this->body = new sf::CircleShape();
	*body = SetCircle(20, sf::Color::Green, Vector2zero());
	body->setOrigin(body->getRadius(), body->getRadius());

	headOffset = sf::Vector2f(body->getRadius() + 10, body->getRadius() / 2);

	this->head = new sf::CircleShape();
	*head = SetCircle(10, sf::Color::Red, this->body->getPosition() + headOffset);
	head->setOrigin(body->getOrigin());

	eyes[0] = sf::CircleShape();
	eyes[0] = SetCircle(2, sf::Color::White, this->body->getPosition().x + 25, this->body->getPosition().y - 5);
	eyes[1] = sf::CircleShape();
	eyes[1] = SetCircle(2, sf::Color::White, this->body->getPosition().x + 25, this->body->getPosition().y + 3);

	this->transform.translate(pos);
}

Turtle::~Turtle()
{
}



void Turtle::appendCommand(Command* cmd)
{
	commands->PushBack(*cmd);
}

Turtle::Command* Turtle::applyCommand(Command* cmd, float dt)
{
	if (cmd == nullptr)
		return nullptr;

	cmd->currentValue -= dt;
	if (cmd->currentValue <= 0)
	{
		return (Command*)commands->RemoveFirst()->next;
	}
	else
	{
		// continuer
		switch (cmd->type)
		{
		case Advance:
			move(sf::Vector2f(cmd->originalValue, 0), dt);
			break;

		case Turn:
			rotate(cmd->originalValue, dt);
			break;

		default:
			break;
		}
	}
	return cmd;
}

void Turtle::move(sf::Vector2f direction, float dt)
{
	this->transform.translate(direction * speed * dt);
}

void Turtle::rotate(float rot, float dt)
{
	this->transform.rotate(rot * rotationSpeed * dt);
}


const sf::Vector2f Turtle::getPosition()
{
	return this->body->getPosition();
}

void Turtle::update(float dt)
{
	currCmd = applyCommand(currCmd, dt);
}

void Turtle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto originalStates = states; // save for later 'reset'

	const auto& transform = this->transform;
	states.transform *= transform;
	target.draw(*body, states);
	states = originalStates;
	states.transform *= this->transform;
	target.draw(*head, states);

	target.draw(eyes[0], states);
	target.draw(eyes[1], states);
}
