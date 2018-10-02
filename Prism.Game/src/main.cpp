#pragma once
#include <iostream>
#include "Window.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "InputManager.h"
#include "Key.h"
#include "ECS/SystemManager.h"
#include "assimp/Importer.hpp"
#include "Renderer/TestRenderer.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "StateMachine.h"
#include "MenuState.h"
#include <cstdlib>
#include <crtdbg.h>
#include <cstdlib>  
#include <crtdbg.h> 
#include "ECS/Components/Component.h"

void StateMachineTest() {
	StateMachine sm;
	MenuState ms;
	sm.addState(ms);
	sm.setState<MenuState>();
	sm.getCurrentState()->onEnter();
}

// This function makes sure all objects are cleared from the stack before the memory gets dumped.

void start() 
{
	Assimp::Importer importer;
	Window window;
	InputManager inputManager;
	window.init("Prism", 1920, 1080, 100, 100);
	window.createOpenGLContext(3, 2, true);
	Renderer::TestRenderer cr;
	cr.init();
	while (!window.shouldClose()) {
		if (inputManager.isKeyPressed(Key::KEY_W)) {
			std::cout << "Key W is pressed!" << std::endl;
		}
		cr.draw();
		window.swapScreen();
	}
}

int main(int argc, char ** argv) {
	start();
	_CrtDumpMemoryLeaks();
	return 0;
}