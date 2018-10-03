#pragma once
#include <Window.h>

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
	int deltaTime;

	Window *window;
	StateMachine *stateMachine;
};

