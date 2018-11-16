#include "InputManager.h"
#include <SDL2/SDL.h>
#include "Key.h"

InputManager::InputManager() {
	keyMap[Key::KEY_W] = SDL_SCANCODE_W;
	keyMap[Key::KEY_A] = SDL_SCANCODE_A;
	keyMap[Key::KEY_S] = SDL_SCANCODE_S;
	keyMap[Key::KEY_D] = SDL_SCANCODE_D;
	keyMap[Key::KEY_Q] = SDL_SCANCODE_Q;
	keyMap[Key::KEY_E] = SDL_SCANCODE_E;
	keyMap[Key::KEY_UP] = SDL_SCANCODE_UP;
	keyMap[Key::KEY_DOWN] = SDL_SCANCODE_DOWN;
	keyMap[Key::KEY_LEFT] = SDL_SCANCODE_LEFT;
	keyMap[Key::KEY_RIGHT] = SDL_SCANCODE_RIGHT;
	keyMap[Key::KEY_ESCAPE] = SDL_SCANCODE_ESCAPE;
	buttonMap[Key::MOUSE_BUTTON_LEFT] = SDL_BUTTON_LEFT;
}

bool InputManager::isKeyPressed(Key key) const
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[keyMap.at(key)])
		return true;

	return false;
}

bool InputManager::isMouseButtonPressed(Key key)
{
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(buttonMap[key])) {
		return true;
	}
	return false;
}

std::vector<int> InputManager::GetMousePoisiton() const
{
	int x;
	int y;
	std::vector<int> posVector;
	const Uint8 currentMouseStates = SDL_GetMouseState(&x, &y);
	posVector.push_back(x);
	posVector.push_back(y);

	return posVector;
}

InputManager::~InputManager()
= default;