#include "InputManager.h"
#include <SDL2/SDL.h>
#include "Key.h"


InputManager::InputManager() {
	keyMap[Key::KEY_W] = SDL_SCANCODE_W;
	keyMap[Key::KEY_A] = SDL_SCANCODE_A;
	keyMap[Key::KEY_S] = SDL_SCANCODE_S;
	keyMap[Key::KEY_D] = SDL_SCANCODE_D;
}

bool InputManager::isKeyPressed(Key key)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	if (currentKeyStates[keyMap[key]]) 
		return true;

	return false;
}

InputManager::~InputManager()
= default;