#pragma once
#include "stdafx.hpp"
class AudioManager
{
private:

	sf::Music globalMusic;
	float musicVolume = 50;

public:

	AudioManager();
	~AudioManager();

	void setMusic(const char* musicPath, float volume = -1);
	void changeMusicVolume(float volume);

};

