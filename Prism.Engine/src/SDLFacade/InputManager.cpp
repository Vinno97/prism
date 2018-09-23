#include "InputManager.h"
#include <SDL2/SDL.h>


InputManager::InputManager()
= default;

bool InputManager::isKeyPressed(SDL_Scancode /*unused*/)
{
	return false;
}


InputManager::~InputManager()
= default;
