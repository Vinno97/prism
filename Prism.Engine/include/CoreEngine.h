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
	/// <summary>
	/// Creates a new coreEngine
	/// </summary>
	CoreEngine();

	/// <summary>
	/// initialize the coreEngine
	/// </summary>
	/// <param name="state">The first state</param>
	template<typename T, typename = std::enable_if_t < std::is_base_of<State, T>::type::value>>
	void setEntryPoint(T& state) {
		addState(state);
		context.stateMachine->setState<T>();
	}

	/// <summary>
	/// adds a state to the statemachine
	/// </summary>
	/// <param name="state">The state that will be added</param>
	template<typename T, typename = std::enable_if_t < std::is_base_of<State, T>::type::value>>
	void addState(T& state) {
		context.stateMachine->addState(state);
		context.stateMachine->getState<T>()->onInit(context);
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

