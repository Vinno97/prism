#pragma once
#include <Window.h>
#include "StateMachine.h"

class Context
{
public:
	Context();
	~Context();

	double deltaTime;
	Window *window;
	StateMachine *stateMachine;
};

