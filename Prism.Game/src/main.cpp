#pragma once
#include <iostream>
#include "CoreEngine.h"
#include "Window.h"
#include "InputManager.h"
#include "Key.h"
#include "Game.h"
#include <string>
#include "Context.h"
#include "StateMachine.h"

#define _CRTDBG_MAP_ALLOC

//QQQ Remove this main method
int main(int argc, char ** argv) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game g = Game();
	State *gPtr = &g;
	CoreEngine *ce = new CoreEngine(gPtr);
	std::string title = "prism";
	ce->CreateWindow(&title[0], 500, 500, 100, 100);
	ce->Run();

	//delete gPtr; 
	delete ce;
	
	

	return 0;
	_CrtDumpMemoryLeaks();
}