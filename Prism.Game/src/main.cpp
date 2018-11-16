#pragma once
#include <cstdlib>  
#include <crtdbg.h> 
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
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "Context.h"
#include "StateMachine.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/MotionSystem.h"
#include "Physics/BoundingBox.h"
#include "Physics/QuadTree.h"
#include "States/PrismGame.h"

#define _CRTDBG_MAP_ALLOC

// This function makes sure all objects are cleared from the stack before the memory gets dumped.
void start() {
	CoreEngine ce = CoreEngine();
	ce.InitWindow("prism", 1920 / 2, 1080 / 2, 100, 100);
	States::PrismGame prism;
	ce.setEntryPoint(prism);
	ce.Run();
}

void test() {
	QuadTree q = QuadTree(10, 10, 0, 0);
	BoundingBox b1 = BoundingBox(2, 3, 3);
	BoundingBox b2 = BoundingBox(2, 7, 3);
	q.Insert(b1);
	q.Insert(b2);
	q.Insert(b1);
	std::vector<BoundingBox const *> v;
	q.Retrieve(v,b1);
	q.Clear();
	q.Insert(b1);
}

int main(int argc, char ** argv) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	start();
	//test();
	


	_CrtDumpMemoryLeaks();
	return 0;
}