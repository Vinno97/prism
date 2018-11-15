#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include "Key.h"

class InputManager
{
public:
	InputManager();

	/// <summary>
	/// Check if a certain key is pressed.
	/// </summary>
	/// <param name="key">A key value of the Key enum type.</param>
	bool isKeyPressed(Key key) const;
	bool isMouseButtonPressed(Key key);
	std::vector<int> GetMousePoisiton() const;

	~InputManager();
private:
	std::map<Key, SDL_Scancode> keyMap;
	std::map<Key, int> buttonMap;
};
