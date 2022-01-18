#include "Game.hpp"

int main()
{
	Game game;
	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}

}