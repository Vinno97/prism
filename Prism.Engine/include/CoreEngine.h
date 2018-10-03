#pragma once
#include <Chrono>
#include <thread>
#include "Context.h"
#include <Window.h>
#include "StateMachine.h"
#include "State.h"

class CoreEngine
{
public:
	template<typename T, typename = std::enable_if < std::is_base_of<State, T>::value>>
	CoreEngine(T state) 
	{
		context.window = new Window();
		context.stateMachine = new StateMachine();
		context.stateMachine->addState(state);
		context.stateMachine->setState<T>();
	}


	const void CreateWindow(const char* title, const int width, const int height, const int x, const int y);
	void Run();
	~CoreEngine();

private:
	Context context;

	void CleanUp();
};

