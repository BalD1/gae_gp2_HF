#pragma once
#include "Entity.hpp"
#include "SFML/Graphics.hpp"
#include "Utility.hpp"

class Turtle : public sf::Transform, public sf::Drawable
{
private:

	sf::CircleShape* body = nullptr;
	sf::CircleShape* head = nullptr;

	sf::Vector2f headOffset;

	float speed = 50;
	float rotationSpeed = 150;

public:

	enum CommandType
	{
		Advance,
		Turn,
	};
	struct Command
	{
		CommandType type = Advance;
		float originalValue = 0;
		float currentValue = 0;
	};

	std::vector<Command> commandList;

	Transform transform;

	Turtle();
	~Turtle();

	void appendCommand(Command* cmd);
	Command* applyCommand(Command* cmd, float dt);

	void move(sf::Vector2f direction, float dt);
	void rotate(float rot, float dt);

	const sf::Vector2f getPosition();

	void update(float dt);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};