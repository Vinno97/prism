#pragma once
#include <SDL2/SDL.h>
#include <map>
#include "Key.h"

class InputManager
{
public:
	InputManager();
	bool isKeyPressed(Key key);
	~InputManager();
private:
	std::map<Key, SDL_Scancode> keyMap;
};

