#include "AudioManager.h"

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(88200, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
	}
	Mix_AllocateChannels(channels);
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

const void AudioManager::playSound(const std::string name, int distance, int loops)
{
	if (sounds.count(name))
	{
		for (int i = 0; i < channels; ++i)
		{
			if (Mix_Playing(i) == 0) {
				int volume = 50 - (distance / 5);
				if (volume < 0) {
					volume = 0;
				}
				
				Mix_Volume(i, volume);
				Mix_PlayChannel(i, sounds[name], loops);
				break;
			}
		}
	}
	else {
		std::runtime_error("Failed to play sound! " + name + " does not exist.");
	}
}

const void AudioManager::playMusic(const std::string name)
{
	if (music.count(name) && current_music_playing != name)
	{
		current_music_playing = name;
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

void AudioManager::stopSound(int channel) const
{
	Mix_HaltChannel(channel);
}

AudioManager::~AudioManager()
{
	sounds.clear();
	music.clear();
	Mix_Quit();
}
