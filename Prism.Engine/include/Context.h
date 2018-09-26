#pragma once
#include <Window.h>

class Context
{
public:
	Context();
	~Context();

	double deltaTime;
	Window *window;
	const StateMachine *stateMachine;
};

