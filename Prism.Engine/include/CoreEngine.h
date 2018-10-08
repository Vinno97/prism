#pragma once
#include <Chrono>
#include <thread>
#include "Context.h"
#include <Window.h>
#include "StateMachine.h"
#include "State.h"

/// <summary>
/// is responsible for running the gameloop
/// </summary>
class CoreEngine
{
public:

	CoreEngine()
	{
		context.window = new Window();
		context.stateMachine = new StateMachine();
		context.inputManager = new InputManager();
	}

	/// <summary>
	/// initialize the coreEngine
	/// </summary>
	/// <param name="state">The first state</param>
	template<typename T, typename = std::enable_if < std::is_base_of<State, T>::value>>
	void setEntryPoint(T state) {
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
	const void InitWindow(const char* title, const int width, const int height, const int x, const int y);

	/// <summary>
	/// Starts the gameloop 
	/// </summary>
	void Run();
	~CoreEngine();

private:
	Context context;
	/// <summary>
	/// frees memorys from the heap
	/// </summary>
	void CleanUp();
};

