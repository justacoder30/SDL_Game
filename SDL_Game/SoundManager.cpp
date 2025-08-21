#include "SoundManager.h"
#include "Sound.h"

std::map<std::string, Sound> SoundManager::sounds;
Mix_Music* SoundManager::bgMusic;

void SoundManager::init()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	bgMusic = Sound::LoadMusic("resource/Music/Heavy.mp3");

	sounds = {
		{"coin", Sound("resource/SoundFX/coin_sound.wav")},
		{"attack", Sound("resource/SoundFX/attack_sound.wav")},
		{"button", Sound("resource/SoundFX/ButtonChose_sound.wav")},
		{"button_click", Sound("resource/SoundFX/ButtonClick_sound.wav")},
		{"Hurt", Sound("resource/SoundFX/Hit_sound.wav")},
		{"landing", Sound("resource/SoundFX/landing_sound.wav")},
		{"WinGame", Sound("resource/SoundFX/WinGame_sound.wav")},
		{"LoseGame", Sound("resource/SoundFX/GameLose_sound.wav")},
	};
}

void SoundManager::PlayMusic()
{
	if (!Mix_PlayingMusic()) Mix_PlayMusic(bgMusic, -1);
	else Mix_ResumeMusic();
}

void SoundManager::PauseMusic()
{
	Mix_PauseMusic();
}

void SoundManager::ResumeMusic()
{
	Mix_ResumeMusic();
}

void SoundManager::StopMusic()
{
	Mix_HaltMusic();
}

void SoundManager::PlaySoundEffect(std::string name)
{
	sounds[name].Play();
}
