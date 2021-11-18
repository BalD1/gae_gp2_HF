#include "Turtle.hpp"

Turtle::Turtle()
{
	transform = Transform();
	this->body = new sf::CircleShape();
	*body = SetCircle(20, sf::Color::Green, Vector2zero());
	body->setOrigin(body->getRadius(), body->getRadius());

	headOffset = sf::Vector2f(body->getRadius() + 10, body->getRadius() / 2);

	this->head = new sf::CircleShape();
	*head = SetCircle(10, sf::Color::Red, this->body->getPosition() + headOffset);
	head->setOrigin(body->getOrigin());
}

Turtle::~Turtle()
{
}



void Turtle::appendCommand(Command* cmd)
{
	commandList.push_back(*cmd);
}

Turtle::Command* Turtle::applyCommand(Command* cmd, float dt)
{
	cmd->currentValue -= dt;
	if (cmd->currentValue <= 0)
	{
		// suppr self
		//return next;
	}
	else
	{
		// continuer
		switch (cmd->type)
		{
		case Advance:
			break;

		case Turn:
			break;

		default:
			break;
		}
	}
	return nullptr;
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
}
