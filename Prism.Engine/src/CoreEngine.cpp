#pragma once
#include "CoreEngine.h"

CoreEngine::CoreEngine(int windowWidth, int windowHeight, const double frameRate, StateMachine *stateMachine) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->isRunning = false;
	this->frameTime = 1.0 / frameRate;
	this->stateMachine = stateMachine; //// ????
}



const void CoreEngine::Start() {
	if (isRunning) {
		return; //The game is already running
	}
	Run();
}

void CoreEngine::Run() {
	isRunning = true;

	auto lastTime = std::chrono::system_clock::now();
	double unprocessedTime = 0;

	while (isRunning) {
		auto startTime = std::chrono::system_clock::now();
		double deltaTime = (startTime - lastTime).count(); //Deltatime in milliseconds

		unprocessedTime += deltaTime; //Passedtime has yet to be processed
		context->deltaTime = deltaTime;

		while (unprocessedTime > frameTime) {
			unprocessedTime -= frameTime;
			// if(window == closed){stop();}
		}
	}
	CoreEngine::CleanUp();
}

void CoreEngine::Stop() {
	if (!isRunning) {
		return; //The game has already stopped
	}
	isRunning = false;
}

void CoreEngine::CleanUp() {
	//Free memory
}

CoreEngine::~CoreEngine()
= default;
