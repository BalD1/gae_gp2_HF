#include "DeathZone.hpp"

DeathZone::DeathZone(float _cx, float _cy, int _stride)
	: Entity(_cx, _cy, _stride)
{
	this->texture = new sf::Texture();
	if (!texture->loadFromFile("Assets/Graphs/red.png"))
		printf("Samus texture could not be loaded in Assets/Graphs/red.png");

	this->spr = new sf::Sprite();
	this->spr->setTexture(*texture);
	syncSprite(1);
}

DeathZone::~DeathZone()
{
}
