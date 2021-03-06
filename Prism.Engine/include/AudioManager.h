#pragma once
#include <string>
#include <map>
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "Util/FileSystem.h"

class AudioManager
{
public:
	AudioManager();
	const int channels = 64;
	std::map<std::string, Mix_Chunk *> sounds;
	std::map<std::string, Mix_Music *> music;
	std::string current_music_playing;

	void addSound(const std::string name, const std::string file);
	void addMusic(const std::string name, const std::string file);

	const int playSound(const std::string name, double distance, int loops = 0);
	const void playMusic(const std::string name);
	void pauseMusic() const;
	void resumeMusic() const;
	void stopMusic() const;
	void stopSound(int channel = -1) const;

	~AudioManager();
private:
	Util::FileSystem fs;
};

