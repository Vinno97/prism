#include "AudioManager.h"

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(88200, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
	}
	Mix_AllocateChannels(channels);
	Mix_VolumeMusic(60);
}


void AudioManager::addSound(const std::string name, const std::string file)
{

	auto filepath = fs.getResourcePath("audio/sounds/") += file;
	Mix_Chunk *sound = Mix_LoadWAV(filepath.c_str());

	if (sound == nullptr) {
		std::string error = "Failed to load sound effect! SDL_mixer Error: ";
		error += Mix_GetError();
		throw std::runtime_error(error.c_str());
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
		throw std::runtime_error(error.c_str());
	}
	else {
		music.emplace(name, mus);
	}
}

const int AudioManager::playSound(const std::string name, double distance, int loops)
{
	const float max_distance = 10;
	if (sounds.count(name))
	{
		for (int i = 0; i < channels; ++i)
		{
			if (Mix_Playing(i) == 0) {
				int volume = static_cast<int>(-1. * (MIX_MAX_VOLUME / max_distance) * distance + MIX_MAX_VOLUME);
				if (volume < 0) { volume = 0;}

				Mix_Volume(i, volume);
				return Mix_PlayChannel(i, sounds[name], loops);
				break;
			}
		}
	}
	else {
		throw std::runtime_error("Failed to play sound! " + name + " does not exist.");
	}
}

const void AudioManager::playMusic(const std::string name)
{
	if (music.count(name))
	{
	    if (current_music_playing != name) {
            current_music_playing = name;
            Mix_PlayMusic(music[name], -1);
        }
	}
	else {
		throw std::runtime_error("Failed to play music! " + name + " does not exist.");
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
	for (auto const& x : sounds) {
		Mix_FreeChunk(x.second);
	}
	for (auto const& x : music) {
		Mix_FreeMusic(x.second);
	}
	sounds.clear();
	music.clear();
	Mix_Quit();
}
