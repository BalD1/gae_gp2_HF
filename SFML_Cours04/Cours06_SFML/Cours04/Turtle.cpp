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

	pencil = SetCircle(5, sf::Color::White, Vector2zero());
	pencil.setOrigin(pencil.getRadius(), pencil.getRadius());
	pencil.setPosition(this->body->getPosition().x, this->body->getPosition().y);

	turtleTexture = new sf::RenderTexture();
	turtleTexture->create(2048, 2048);
	turtleTexture->clear(sf::Color(0, 0, 0, 0));

	this->transform.translate(pos);
	baseTransform = this->transform;
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
		if (commandsSave == nullptr)
		{
			CommandList* sCmdL = new CommandList(cmdList->cmd->type, cmdList->cmd->originalValue, cmdList->cmd->speed);
			commandsSave = sCmdL;
		}
	}
	else
	{
		commands->PushBack(cmdList->cmd);
		CommandList::Command* sCmd = new CommandList::Command();
		sCmd->originalValue = cmdList->cmd->originalValue;
		sCmd->speed = cmdList->cmd->speed;
		sCmd->type = cmdList->cmd->type;
		commandsSave->PushBack(sCmd);
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
		CommandList::Command* sCmd = new CommandList::Command();
		sCmd->originalValue = cmd->originalValue;
		sCmd->speed = cmd->speed;
		sCmd->type = cmd->type;
		commandsSave->PushBack(sCmd);
	}
}
void Turtle::appendCommand(const CommandList::CommandType _type, const float value, float _speed)
{
	if (_speed == -1)
	{
		if (_type == CommandList::CommandType::Advance)
			_speed = this->speed;
		else if (_type == CommandList::CommandType::Turn)
			_speed = this->rotationSpeed;
	}

	CommandList* _cmd = new CommandList(_type, value, _speed);
	appendCommand(_cmd);
}
void Turtle::appendCommand(const char* _type, const float value,  float _speed )
{
	if (_type == "Advance")
	{
		if (_speed == -1)
			_speed = this->speed;
		appendCommand(CommandList::CommandType::Advance, value, _speed);
	}
	else if (_type == "Turn")
	{
		printf("%f", _speed);
		if (_speed == -1)
		{
			_speed = this->rotationSpeed;
		}
		appendCommand(CommandList::CommandType::Turn, value, _speed);
	}
	else if (_type == "PenUp")
	{
		appendCommand(CommandList::CommandType::PenUp, value, _speed);
	}
	else if (_type == "PenDown")
	{
		appendCommand(CommandList::CommandType::PenDown, value, _speed);
	}
}

void Turtle::cleanCommands()
{
	commands->CleanList();
	commands = nullptr;
}

CommandList* Turtle::applyCommand(CommandList* cmdList, float dt)
{
	if (cmdList == nullptr)
		return nullptr;

	if (cmdList->cmd->originalValue > 0)
	{
		cmdList->cmd->currentValue -= 1.0/60.0;
		if (cmdList->cmd->currentValue < 0)
			return cmdList->RemoveFirst();
	}
	else
	{
		cmdList->cmd->currentValue += 1.0 / 60.0;
		if (cmdList->cmd->currentValue > 0)
			return cmdList->RemoveFirst();

	}

	switch (cmdList->cmd->type)
	{
		case cmdList->Advance:
			cmdMove(NormalizeVector(sf::Vector2f(cmdList->cmd->originalValue, 0)), cmdList->cmd->speed, dt);
			break;

		case cmdList->Turn:
			if (cmdList->cmd->originalValue > 0)
				cmdRotate(1, cmdList->cmd->speed, dt);
			else
				cmdRotate(-1, cmdList->cmd->speed, dt);
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

void Turtle::saveCommandsInFile(const char* filePath)
{
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, filePath, "w");
	if (err != 0)
		printf("The file was not opened\n");
	else
	{
		while (commandsSave != nullptr)
		{
			char curr[256];
			CommandList::Command* tmpCmd = commandsSave->head->cmd;
			sprintf_s(curr, "%s %f %f \n", commandsSave->ConvertEnumToStr(tmpCmd->type), tmpCmd->originalValue, tmpCmd->speed);
			commandsSave = commandsSave->RemoveFirst();
			fprintf(fp, curr);
		}

		fclose(fp);
	}
}

void Turtle::move(sf::Vector2f direction, float dt)
{
	this->transform.translate(direction * speed * dt);
}

void Turtle::cmdMove(sf::Vector2f direction, float _speed, float dt)
{
	this->transform.translate(direction * _speed * dt);
}

void Turtle::rotate(float rot, float dt)
{
	this->transform.rotate(rot * rotationSpeed * dt);
}

void Turtle::cmdRotate(float rot, float _speed, float dt)
{
	this->transform.rotate(rot * _speed * dt);
}

void Turtle::enablePen(bool enabled)
{
	this->renderPen = enabled;
}

void Turtle::changePencilColor(sf::Color _color)
{
	pencil.setFillColor(_color);
}


const sf::Vector2f Turtle::getPosition()
{
	return this->pencil.getPosition();
}

void Turtle::setPosition(sf::Vector2f pos)
{
	this->pencil.setPosition(pos);
}

void Turtle::changeBaseSpeed(const float _speed)
{
	this->speed = _speed;
}

const float Turtle::getBaseSpeed()
{
	return this->speed;
}

void Turtle::changeBaseRotationSpeed(const float _speed)
{
	this->rotationSpeed = _speed;
}

const float Turtle::getBaseRotationSpeed()
{
	return this->rotationSpeed;
}

void Turtle::reset()
{
	cleanCommands();
	turtleTexture->clear(sf::Color(0, 0, 0, 0));
	this->transform = baseTransform;
	renderPen = true;
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