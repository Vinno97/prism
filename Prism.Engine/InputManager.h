#pragma once
#include <SDL.h>

class InputManager
{
public:
	InputManager(SDL_Window *window);
	bool isKeyPressed(SDL_Scancode);
	~InputManager();
};

