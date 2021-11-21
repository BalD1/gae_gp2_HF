#pragma once
#include "Entity.hpp"
#include "SFML/Graphics.hpp"
#include "Utility.hpp"
#include "CommandList.hpp"

class Turtle : public sf::Transform, public sf::Drawable
{
private:

	sf::CircleShape* body = nullptr;
	sf::CircleShape* head = nullptr;
	sf::CircleShape eyes[2];

	sf::Vector2f headOffset;

	float speed = 50;
	float rotationSpeed = 90;

public:

	CommandList* commands = nullptr;

	Transform transform;

	Turtle(sf::Vector2f pos);
	~Turtle();

	void appendCommand(CommandList* cmdList);
	void appendCommand(CommandList::Command* cmd);
	void appendCommand(const CommandList::CommandType _type, const float value);
	void appendCommand(const char* _type, const float value);

	CommandList* applyCommand(CommandList* cmdList, float dt);

	void move(sf::Vector2f direction, float dt);
	void rotate(float rot, float dt);

	const sf::Vector2f getPosition();

	void update(float dt);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void printCommandList();

};