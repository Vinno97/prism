#pragma once
#include <SDL.h>

class InputManager
{
public:
	InputManager();
	bool isKeyPressed(SDL_Scancode);
	~InputManager();
};

