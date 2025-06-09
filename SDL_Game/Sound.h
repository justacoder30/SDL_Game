#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
class Sound
{
private:
	Mix_Chunk* sound;
public:
	Sound();
	Sound(std::string path);
	void Play();
	static Mix_Music* LoadMusic(std::string path);
};

