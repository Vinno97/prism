#include "AudioSystem.h"

AudioSystem::AudioSystem()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
}


void AudioSystem::addSound(string name, string file)
{
	Mix_Chunk *sound = Mix_LoadWAV((soundFolder + file).c_str());

	if (sound == NULL) {
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	else {
		sounds.emplace(name, sound);
	}
}

void AudioSystem::addMusic(string name, string file)
{
	Mix_Music *mus = Mix_LoadMUS((musicFolder + file).c_str());
	
	if (mus == NULL) {
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	else {
		music.emplace(name, mus);
	}
}

void AudioSystem::playSound(string name)
{
	Mix_PlayChannel(-1, sounds[name], 0);
}

void AudioSystem::playMusic(string name)
{
	Mix_PlayMusic(music[name], -1);
}

void AudioSystem::pauseOrResumeMusic()
{
	if (Mix_PlayingMusic() == 1)
	{
		if (Mix_PausedMusic() == 1) {
			Mix_ResumeMusic();
		}
		else {
			Mix_PauseMusic();
		}
	}
}

void AudioSystem::stopMusic()
{
	Mix_HaltMusic();
}

AudioSystem::~AudioSystem()
{
	sounds.clear();
	music.clear();
	Mix_Quit();
}