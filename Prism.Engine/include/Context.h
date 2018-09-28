#pragma once
#include <Window.h>

class StateMachine;
class Context
{
public:
	Context();
	~Context();

	double deltaTime;
	Window *window;
	StateMachine *stateMachine;
};

