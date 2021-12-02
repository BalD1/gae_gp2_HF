#pragma once
#include "Entity.hpp"

class Wall : public Entity
{
private:

public:

	Wall(float _cx, float _cy, int _stride);
	~Wall();
};

