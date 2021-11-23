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

	pencil = SetCircle(5, sf::Color::White, this->body->getPosition().x - 25, this->body->getPosition().y);

	turtleTexture = new sf::RenderTexture();
	turtleTexture->create(2048, 2048);
	turtleTexture->clear(sf::Color(0, 0, 0, 0));

	this->transform.translate(pos);
}

Turtle::~Turtle()
{
	delete commands;
	delete this->body;
	delete this->head;
}



void Turtle::appendCommand(CommandList* cmdList)
{
	if (commands == nullptr)
	{
		commands = cmdList;
	}
	else
	{
		commands->PushBack(cmdList->cmd);
		delete cmdList;
	}
}
void Turtle::appendCommand(CommandList::Command* cmd)
{
	if (commands == nullptr)
	{
		commands = new CommandList(cmd);
	}
	else
	{
		commands->PushBack(cmd);
	}
}
void Turtle::appendCommand(const CommandList::CommandType _type, const float value)
{
	CommandList* _cmd = new CommandList(_type, value);
	appendCommand(_cmd);
}
void Turtle::appendCommand(const char* _type, const float value)
{

	if (_type == "Advance")
	{
		appendCommand(CommandList::CommandType::Advance, value);
	}
	else if (_type == "Turn")
	{
		appendCommand(CommandList::CommandType::Turn, value);
	}
	else if (_type == "PenUp")
	{
		appendCommand(CommandList::CommandType::PenUp, value);
	}
	else if (_type == "PenDown")
	{
		appendCommand(CommandList::CommandType::PenDown, value);
	}
}

CommandList* Turtle::applyCommand(CommandList* cmdList, float dt)
{
	if (cmdList == nullptr)
		return nullptr;

	if (cmdList->cmd->originalValue > 0)
	{
		cmdList->cmd->currentValue -= dt;
		if (cmdList->cmd->currentValue <= 0)
			return cmdList->RemoveFirst();
	}
	else
	{
		cmdList->cmd->currentValue += dt;
		if (cmdList->cmd->currentValue >= 0)
			return cmdList->RemoveFirst();

	}

	switch (cmdList->cmd->type)
	{
		case cmdList->Advance:
			move(NormalizeVector(sf::Vector2f(cmdList->cmd->originalValue, 0)), dt);
			break;

		case cmdList->Turn:
			if (cmdList->cmd->originalValue > 0)
				rotate(1, dt);
			else
				rotate(-1, dt);
			break;

		case cmdList->PenUp:
			renderPen = false;
			cmdList->cmd->currentValue = 0;
			break;

		case cmdList->PenDown:
			renderPen = true;
			cmdList->cmd->currentValue = 0;
			break;

		default:
			break;
	}

	return cmdList;
}

void Turtle::move(sf::Vector2f direction, float dt)
{
	this->transform.translate(direction * speed * dt);
}

void Turtle::rotate(float rot, float dt)
{
	this->transform.rotate(rot * rotationSpeed * dt);
}

void Turtle::changePencilColor(sf::Color _color)
{
	pencil.setFillColor(_color);
}


const sf::Vector2f Turtle::getPosition()
{
	return this->body->getPosition();
}

void Turtle::setPosition(sf::Vector2f pos)
{
	this->pencil.setPosition(pos);
}

void Turtle::update(float dt)
{
	commands = applyCommand(commands, dt);
}

void Turtle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto originalStates = states;
	const auto& transform = this->transform;

	states = originalStates;
	states.transform *= this->transform;

	if (renderPen)
		turtleTexture->draw(pencil, states);

	turtleTexture->display();

	sf::Sprite spr(turtleTexture->getTexture());
	target.draw(spr);

	target.draw(*body, states);
	target.draw(*head, states);
	target.draw(eyes[0], states);
	target.draw(eyes[1], states);

	/*
	auto originalStates = states;

	const auto& transform = this->transform;
	states.transform *= transform;
	target.draw(*body, states);
	states = originalStates;
	*/
}

void Turtle::printCommandList()
{
	commands->PrintList();
}