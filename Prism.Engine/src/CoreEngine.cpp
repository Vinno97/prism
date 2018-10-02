#include "CoreEngine.h"


CoreEngine::CoreEngine(State *beginState) {
	context.stateMachine = new StateMachine();
	context.stateMachine->setState<beginState>;
	context.window = new Window();
}

const void CoreEngine::CreateWindow(const char* title, const int width, const int height, const int x, const int y) {
	context.window->init(title, width, height, x, y);
}

//Runns the gameloop
void CoreEngine::Run() 
{
	//Holds the time in which the gameupdate was last called 
	auto lastTime = std::chrono::system_clock::now();
	int count = 0;

	//While the window is unclosed run the gameloop
	while (!context.window->shouldClose()) 
	{
		//Holds the time in which the current gameupdat is being called
		auto startTime = std::chrono::system_clock::now();
		
		//Deltatime in microseconds
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(startTime - lastTime); 
		lastTime = startTime;

		//Sets the right values in context
		context.deltaTime = deltaTime.count();
		context.stateMachine->getCurrentState()->onUpdate(context);
	}
}

void CoreEngine::CleanUp() {
	//Free memory
	delete context.stateMachine;
	delete context.window;
}

CoreEngine::~CoreEngine()
{
	CleanUp();
}
