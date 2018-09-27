#include "CoreEngine.h"


CoreEngine::CoreEngine(State *beginState) {
	context.stateMachine = new StateMachine();
	context.stateMachine->setState(beginState);
	context.window = new Window();
}

void CoreEngine::CreateWindow(const char* title, const int width, const int height, const int x, const int y) {
	context.window->init(title, width, height, x, y);
}

void CoreEngine::Run() {
	

	auto lastTime = std::chrono::system_clock::now();

	while (!context.window->shouldClose()) {
		auto startTime = std::chrono::system_clock::now();
		//Deltatime in milliseconds
		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(startTime - lastTime); 
		lastTime = startTime;

		context.deltaTime = deltaTime.count();

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
