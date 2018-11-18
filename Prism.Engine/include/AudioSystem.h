#pragma once
#include <string>
#include <map>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

using namespace std;

class AudioSystem
{
public:
	AudioSystem();
	
	string soundFolder = "audio/sounds/";
	string musicFolder = "audio/music/";

	map<string, Mix_Chunk *> sounds;
	map<string, Mix_Music *> music;
	
	void addSound(string name, string file);
	void addMusic(string name, string file);

	void playSound(string name);
	void playMusic(string name);
	void pauseOrResumeMusic();
	void stopMusic(); 

	~AudioSystem();
};

