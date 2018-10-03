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

	/// <summary>
	/// Create new window 
	/// </summary>
	/// <param name="title">Title of the current window</param>
	/// <param name="width">Width of window</param>
	/// <param name="height">Height of window</param>
	/// <param name="x">X position of window</param>
	/// <param name="y">Y position of window</param>
	const void CreateWindow(const char* title, const int width, const int height, const int x, const int y);
	void Run();
	~CoreEngine();

private:
	Context context;

	void CleanUp();
};

