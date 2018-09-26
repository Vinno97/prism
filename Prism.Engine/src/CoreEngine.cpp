#pragma once
#include "CoreEngine.h"


CoreEngine::CoreEngine(double tps) {
	this->isRunning = false;
	this->tikTime = 1.0 / tps;
	//this->stateMachine = stateMachine; //// ????
}

void CoreEngine::CreateContext(const char* title, const int width, const int height, const int x, const int y, StateMachine *stateMachine) {
	context = Context();
	context.window = new Window();
	context.window->init(title, width, height, x, y);
	context.stateMachine = stateMachine;
}

const void CoreEngine::Start() {
	if (isRunning) {
		//The game is already running
		return; 
	}
	Run();
}

void CoreEngine::Run() {
	isRunning = true;

	auto lastTime = std::chrono::system_clock::now();
	double unprocessedTime = 0.0;

	while (!context.window->shouldClose()) {
		auto startTime = std::chrono::system_clock::now();
		//Deltatime in milliseconds
		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(startTime - lastTime); 

		//Passedtime has yet to be processed
		unprocessedTime += deltaTime.count(); 
		context.deltaTime = deltaTime.count();

		while (unprocessedTime > tikTime) {
			unprocessedTime -= tikTime;
			

			//statemachine.update(context);
			
		}
		try
		{
			//Sleep 1 ms
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		catch (std::exception e)
		{
			std::cout<<e.what()<<std::endl;
		}
	}
	CleanUp();
}



void CoreEngine::CleanUp() {
	//Free memory
}

CoreEngine::~CoreEngine()
= default;
