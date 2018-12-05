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
	
	std::map<std::string, Mix_Chunk *> sounds;
	std::map<std::string, Mix_Music *> music;
	std::string current_music_playing;

	void addSound(const std::string name, const std::string file);
	void addMusic(const std::string name, const std::string file);

	const void playSound(const std::string name);
	const void playMusic(const std::string name);
	void pauseMusic() const;
	void resumeMusic() const;
	void stopMusic() const;

	~AudioManager();
private:
	Util::FileSystem fs;
};

