#include "Game.hpp"
#include "AudioManager.hpp"

int main()
{
	Game game;
	AudioManager audioManager;
	audioManager.setMusic("Assets/Sounds/music.ogg");

	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}

}