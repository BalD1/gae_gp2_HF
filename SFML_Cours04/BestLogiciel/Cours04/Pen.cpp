#include "Pen.hpp"

Pen::Pen(sf::Vector2f pos)
{
	pencil = SetCircle(5, sf::Color::White, pos);

	drawableSpace = new sf::RenderTexture();
	drawableSpace->create(2048, 2048);
	drawableSpace->clear(sf::Color(0, 0, 0, 0));
}

Pen::~Pen()
{
	free(drawableSpace);
}

void Pen::enablePen(bool enabled)
{
	renderPen = enabled;
}

void Pen::changePencilColor(sf::Color _color)
{
	pencil.setFillColor(_color);
}

const sf::Vector2f Pen::getPosition()
{
	return pencil.getPosition();
}

void Pen::setPosition(sf::Vector2f pos)
{
	pencil.setPosition(pos);
}

void Pen::setPosition(float posX, float posY)
{
	pencil.setPosition(sf::Vector2f(posX, posY));
}

void Pen::update(float dt)
{
}

void Pen::render(sf::RenderTarget& target)
{
	if (renderPen)
		drawableSpace->draw(pencil);

	drawableSpace->display();

	sf::Sprite spr(drawableSpace->getTexture());
	target.draw(spr);

	target.draw(pencil);
}
