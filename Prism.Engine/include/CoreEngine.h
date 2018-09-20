#pragma once
#include <Chrono>
#include "StateMachine.h"
#include "Context.h"
#include "window.h"
class CoreEngine
{
public:
	const void Start();
	void Stop();
	void Run();
	
	CoreEngine(int windowWidth, int windowHeight, const double frameRate, StateMachine *stateMachine);
	~CoreEngine();

private:
	int windowWidth;
	int windowHeight;
	bool isRunning;
	double frameTime;
	Context *context;
	StateMachine *stateMachine;

	void CleanUp();
};

