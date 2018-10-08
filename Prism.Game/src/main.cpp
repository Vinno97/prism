#pragma once
#include <iostream>
#include "CoreEngine.h"
#include "Window.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "InputManager.h"
#include "Key.h"
#include "Game.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "Context.h"
#include "StateMachine.h"
#include "Renderer/TestRenderer.h"

#define _CRTDBG_MAP_ALLOC

//QQQ Remove this main method
void test() {
	State st;
	CoreEngine ce = CoreEngine(st);
	ce.CreateWindow("prism", 500, 500, 100, 100);
	ce.Run();
}

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
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	test();
	_CrtDumpMemoryLeaks();
	return 0;
}