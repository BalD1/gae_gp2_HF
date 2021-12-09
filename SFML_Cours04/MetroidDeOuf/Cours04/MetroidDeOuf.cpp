#include "Game.hpp"
#include "AudioManager.hpp"

int main()
{
	Game game;
	static int cc = 1;
	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}

}