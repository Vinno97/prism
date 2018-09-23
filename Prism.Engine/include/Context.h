#pragma once

#include "InputManager.h"

class Context
{
public:
	Context();
	~Context();

	InputManager* inputManager;
	int deltaTime;
};

