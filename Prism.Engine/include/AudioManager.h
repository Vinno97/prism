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

	void addSound(std::string name, std::string file);
	void addMusic(std::string name, std::string file);

	const void playSound(std::string name, int distance, int loops = 0);
	const void playMusic(std::string name);
	void pauseMusic() const;
	void resumeMusic() const;
	void stopMusic() const;
	void stopSound(int channel = -1) const;

	~AudioManager();
private:
	Util::FileSystem fs;
};
