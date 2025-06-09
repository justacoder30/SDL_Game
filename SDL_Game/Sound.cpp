#include "Sound.h"

Sound::Sound()
{}

Sound::Sound(std::string path)
{
    sound = Mix_LoadWAV(path.c_str());
    if (sound == NULL)
    {
        printf("Failed to load sound path: %s sound effect! SDL_mixer Error: %s\n", path.c_str(), Mix_GetError());
    }
}

void Sound::Play()
{
    Mix_PlayChannel(-1, sound, 0);
}

Mix_Music* Sound::LoadMusic(std::string path)
{
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (music == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
    }
    return music;
}
