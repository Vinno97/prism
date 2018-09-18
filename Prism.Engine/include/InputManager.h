#pragma once
#include <SDL2/SDL.h>

class InputManager
{
public:
	InputManager();
	bool isKeyPressed(SDL_Scancode);
	~InputManager();
};

