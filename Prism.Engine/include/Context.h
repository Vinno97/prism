#pragma once
#include <Window.h>
#include "InputManager.h"

class StateMachine;

/// <summary>
/// contains information that are needed to update the states
/// </summary>
struct Context
{
public:
	Context();
	~Context();

	//Holds the time that has been passed since the last gameupdate
	long deltaTime = 0;

	Window *window;
	StateMachine *stateMachine;
	InputManager *inputManager;
};

