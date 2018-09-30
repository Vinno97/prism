#include "CoreEngine.h"


CoreEngine::CoreEngine(State *beginState) {
	context.setStateMachine(new StateMachine());
	context.getStateMachine()->setState(beginState);
	context.setWindow(new Window());
}

const void CoreEngine::CreateWindow(const char* title, const int width, const int height, const int x, const int y) {
	context.getWindow()->init(title, width, height, x, y);
}

//Runns the gameloop
void CoreEngine::Run() 
{
	//Holds the time in which the gameupdate was last called 
	auto lastTime = std::chrono::system_clock::now();
	int count = 0;

	//While the window is unclosed run the gameloop
	while (!context.getWindow()->shouldClose()) 
	{
		//Holds the time in which the current gameupdat is being called
		auto startTime = std::chrono::system_clock::now();
		
		//Deltatime in microseconds
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(startTime - lastTime); 
		lastTime = startTime;

		//Sets the right values in context
		context.setDeltatime(deltaTime.count());
		State *currentState = context.getStateMachine()->getState();

		//Calls the game update fuction
		currentState->update(context);
	}
}

void CoreEngine::CleanUp() {
	//Free memory
	delete context.getStateMachine();
	delete context.getWindow();
}

CoreEngine::~CoreEngine()
{
	CleanUp();
}
