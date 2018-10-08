#pragma once
#include <cstdlib>  
#include <crtdbg.h> 
#include <iostream>
#include "CoreEngine.h"
#include "PrismGame.h"

#define _CRTDBG_MAP_ALLOC

// This function makes sure all objects are cleared from the stack before the memory gets dumped.
void start() {
	CoreEngine ce = CoreEngine();
	ce.InitWindow("prism", 1920 / 2, 1080 / 2, 100, 100);

	PrismGame prism;
	ce.setEntryPoint(prism);
	ce.Run();
}

int main(int argc, char ** argv) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	start();

	_CrtDumpMemoryLeaks();
	return 0;
}