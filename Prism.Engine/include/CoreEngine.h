#pragma once
#include <Chrono>
#include <thread>
//#include <memory>
#include "Context.h"
#include <Window.h>
#include "StateMachine.h"
#include "State.h"

class CoreEngine
{
public:
	CoreEngine(State *beginstate);
	const void CreateWindow(const char* title, const int width, const int height, const int x, const int y);
	void Run();
	~CoreEngine();

private:
	Context context;

	void CleanUp();
};

