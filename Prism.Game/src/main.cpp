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
#include <string>
#include "Context.h"
#include "StateMachine.h"

#define _CRTDBG_MAP_ALLOC

//QQQ Remove this main method
void test() {
	State st;
	CoreEngine ce = CoreEngine(st);
	std::string title = "prism";
	ce.CreateWindow(&title[0], 500, 500, 100, 100);
	ce.Run();

}

int main(int argc, char ** argv) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	
	test();
	_CrtDumpMemoryLeaks();
	return 0;
}