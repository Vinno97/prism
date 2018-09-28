#pragma once
#include <Window.h>

class StateMachine;
class Context
{
public:
	Context();
	const double getDeltatime();
	Window *getWindow();
	StateMachine *getStateMachine();
	void setDeltatime(int newDeltaTime);
	void setWindow(Window *newWindow);
	void setStateMachine(StateMachine *newStateMachine);
	~Context();


private: 
	int deltaTime;
	Window *window;
	StateMachine *stateMachine;
};

