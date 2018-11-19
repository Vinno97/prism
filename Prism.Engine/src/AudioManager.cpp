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
	auto pwd = fs::current_path();
	auto filepath = pwd.concat("/res/audio/sounds/").concat(file);
	Mix_Chunk *sound = Mix_LoadWAV(filepath.string().c_str());

	if (sound == nullptr) {
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << "\n";
	}
	else {
		sounds.emplace(name, sound);
	}
}

void AudioManager::addMusic(const std::string name, const std::string file)
{
	auto pwd = fs::current_path();
	auto filepath = pwd.concat("/res/audio/music/").concat(file);
	Mix_Music *mus = Mix_LoadMUS(filepath.string().c_str());
	
	if (mus == nullptr) {
		std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << "\n";
	}
	else {
		music.emplace(name, mus);
	}
}

const void AudioManager::playSound(const std::string name)
{
	Mix_PlayChannel(-1, sounds[name], 0);
}

const void AudioManager::playMusic(const std::string name)
{
	Mix_PlayMusic(music[name], -1);
}

void AudioManager::pauseOrResumeMusic()
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

void AudioManager::stopMusic()
{
	Mix_HaltMusic();
}

AudioManager::~AudioManager()
{
	sounds.clear();
	music.clear();
	Mix_Quit();
}