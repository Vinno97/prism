#pragma once
#include <chrono>
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
	/// <summary>
	/// Creates a new coreEngine
	/// </summary>
	CoreEngine();

	/// <summary>
	/// initialize the coreEngine
	/// </summary>
	/// <param name="state">The first state</param>

	template<typename T, typename = std::enable_if_t < std::is_base_of<State, T>::type::value>>
	void setEntryPoint()
	{
		context.stateMachine->setState<T>(context);
	}

	/// <summary>
	/// adds a state to the statemachine
	/// </summary>
	/// <param name="state">The state that will be added</param>

	template<typename T, typename...Fs, typename = std::enable_if_t < std::is_base_of<State, T>::type::value>>
	void addState(Fs&&... fs)
	{
		context.stateMachine->addState<T>(context, std::forward<Fs>(fs)...);
	}

	/// <summary>
	/// Create new window 
	/// </summary>
	/// <param name="title">Title of the current window</param>
	/// <param name="width">Width of window</param>
	/// <param name="height">Height of window</param>
	/// <param name="x">X position of window</param>
	/// <param name="y">Y position of window</param>
	const void InitWindow(const char* title, int width, int height, int x, int y);

	/// <summary>
	/// Starts the gameloop 
	/// </summary>
	void Run();

private:
	Context context;
};

