#include "AudioManager.h"

namespace fs = std::experimental::filesystem;

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
	}
}


void AudioManager::addSound(const std::string name, const std::string file)
{
	
	auto filepath = fs.getResourcePath("audio/sounds/") += file;
	Mix_Chunk *sound = Mix_LoadWAV(filepath.c_str());

	if (sound == nullptr) {
		std::string error = "Failed to load sound effect! SDL_mixer Error: ";
		error += Mix_GetError();
		std::runtime_error(error.c_str());
	}
	else {
		sounds.emplace(name, sound);
	}
}

void AudioManager::addMusic(const std::string name, const std::string file)
{
	auto filepath = fs.getResourcePath("audio/music/") += file;
	Mix_Music *mus = Mix_LoadMUS(filepath.c_str());
	
	if (mus == nullptr) {
		std::string error = "Failed to load music! SDL_mixer Error: ";
		error += Mix_GetError();
		std::runtime_error(error.c_str());
	}
	else {
		music.emplace(name, mus);
	}
}

const void AudioManager::playSound(const std::string name)
{
	if (sounds.count(name))
	{
		Mix_PlayChannel(-1, sounds[name], 0);
	}
	else {
		std::runtime_error("Failed to play sound! " + name + " does not exist.");
	}
}

const void AudioManager::playMusic(const std::string name)
{
	if (music.count(name))
	{
		Mix_PlayMusic(music[name], -1);
	}
	else {
		std::runtime_error("Failed to play music! " + name + " does not exist.");
	}
}

void AudioManager::pauseMusic() const
{
	if (Mix_PlayingMusic() == 1 && Mix_PausedMusic() == 0)
	{
		Mix_PauseMusic();
	}
}

void AudioManager::resumeMusic() const
{
	if (Mix_PlayingMusic() == 1 && Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}
}

void AudioManager::stopMusic() const
{
	Mix_HaltMusic();
}

AudioManager::~AudioManager()
{
	sounds.clear();
	music.clear();
	Mix_Quit();
}