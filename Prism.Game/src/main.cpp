#pragma once

#include <cstdlib>
//#include <crtdbg.h>
#include <iostream>
#include "CoreEngine.h"
#include "InputManager.h"
#include "Key.h"
#include "Window.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/Component.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "InputManager.h"
#include "Key.h"
#include "Game.h"
#include <string>
#include "Context.h"
#include "StateMachine.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/MotionSystem.h"
#include "Physics/BoundingBox.h"
#include "Physics/QuadTree.h"
#include "States/MainMenuState.h"
#include "States/CreditsState.h"
#include "States/ResolutionMenuState.h"

#define _CRTDBG_MAP_ALLOC

// This function makes sure all objects are cleared from the stack before the memory gets dumped.
void start() {
    CoreEngine ce = CoreEngine();
	srand(time(NULL));
    ce.InitWindow("prism", 1920 / 2, 1080 / 2, 0, 0);
    ce.addState<States::MainMenuState>();
    ce.setEntryPoint<States::MainMenuState>();

    ce.Run();
}

int main(int argc, char **argv) {
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    start();

//	_CrtDumpMemoryLeaks();
    return 0;
}
