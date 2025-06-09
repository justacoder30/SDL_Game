#pragma once
#include <SDL2/SDL_mixer.h>
#include "Sound.h"
#include <map>
#include <string>
class SoundManager
{
private:
	static Mix_Music* bgMusic;
	static std::map<std::string, Sound> sounds;
public:
	static void init();
	static void PlayMusic();
	static void PauseMusic();
	static void ResumeMusic();
	static void StopMusic();
	static void PlaySoundEffect(std::string name);
};

