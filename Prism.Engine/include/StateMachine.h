#pragma once
#include "State.h"

class StateMachine
{
public:
	StateMachine();
	~StateMachine();
	State getState();
	void setState(State newState);

private:
	State *currentState = nullptr;
};


