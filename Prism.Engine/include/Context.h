#pragma once
#include <memory>
#include "Window.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "StateMachine.h"


class StateMachine;

/// <summary>
/// contains information that are needed to update the states
/// </summary>
struct Context
{
public:
	Context();
	~Context();

	//Holds the time that has been passed since the last gameupdate
	float deltaTime = 0;

	std::unique_ptr<Window> window;
	std::unique_ptr<StateMachine> stateMachine;
	std::unique_ptr<InputManager> inputManager;
	std::unique_ptr<AudioManager> audioManager;
};

