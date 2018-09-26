#pragma once
#include <Chrono>
#include <thread>
#include "Context.h"
#include "window.h"
class CoreEngine
{
public:
	const void Start();
	void Run();
	
	CoreEngine(const double frameRate);
	void CreateContext(const char* title, const int width, const int height, const int x, const int y, StateMachine *stateMachine);
	~CoreEngine();

private:
	bool isRunning;
	double tikTime;
	Context context;
	//const StateMachine *stateMachine;

	void CleanUp();
};

