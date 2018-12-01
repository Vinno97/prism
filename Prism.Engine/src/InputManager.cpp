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
	keyMap[Key::KEY_H] = SDL_SCANCODE_H;
	keyMap[Key::KEY_1] = SDL_SCANCODE_1;
	keyMap[Key::KEY_2] = SDL_SCANCODE_2;
	keyMap[Key::KEY_3] = SDL_SCANCODE_3;
	keyMap[Key::KEY_TAB] = SDL_SCANCODE_TAB;
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