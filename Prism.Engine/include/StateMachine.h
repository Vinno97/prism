#pragma once
#include "State.h"

struct StateMachine
{
public:
	StateMachine();
	~StateMachine();
	State* getState();
	void setState(State *newState);

private:
	State *currentState;
};


