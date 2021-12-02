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

	sf::CircleShape pencil;

	sf::Vector2f headOffset;

	sf::RenderTexture* turtleTexture = nullptr;

	bool renderPen = true;

	float speed = 50;
	float rotationSpeed = 90;

public:

	CommandList* commands = nullptr;
	CommandList* commandsSave = nullptr;

	Transform transform;
	Transform baseTransform;

	Turtle(sf::Vector2f pos);
	~Turtle();

	void appendCommand(CommandList* cmdList);
	void appendCommand(CommandList::Command* cmd);
	void appendCommand(const CommandList::CommandType _type, const float value,  float _speed = -1);
	void appendCommand(const char* _type, const float value,  float _speed = -1);

	void cleanCommands();

	CommandList* applyCommand(CommandList* cmdList, float dt);

	void saveCommandsInFile(const char* filePath);

	void move(sf::Vector2f direction, float dt);
	void cmdMove(sf::Vector2f direction, float _speed, float dt);
	void rotate(float rot, float dt);
	void cmdRotate(float rot, float _speed, float dt);

	void enablePen(bool enabled);
	void changePencilColor(sf::Color _color);

	const sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void changeBaseSpeed(const float _speed);
	const float getBaseSpeed();
	void changeBaseRotationSpeed(const float _speed);
	const float getBaseRotationSpeed();

	void reset();

	void update(float dt);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void printCommandList();

};