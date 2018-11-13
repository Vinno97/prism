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
#include "PrismGame.h"
#include "Physics/BoundingBox.h"
#include "Physics/QuadTree.h"

#define _CRTDBG_MAP_ALLOC

// This function makes sure all objects are cleared from the stack before the memory gets dumped.
void start() {
	CoreEngine ce = CoreEngine();
	ce.InitWindow("prism", 1920 / 2, 1080 / 2, 100, 100);
	PrismGame prism;
	ce.setEntryPoint(prism);
	ce.Run();
}

void test() {
	Physics::QuadTree q = Physics::QuadTree(50,50,0,0,2);
	Physics::BoundingBox b = Physics::BoundingBox(2, 1, 0);
	q.Insert(b);
	q.Insert(Physics::BoundingBox(2, 0, 0));
	q.Insert(Physics::BoundingBox(2, 1, 1));
	q.Insert(Physics::BoundingBox(2, 40, 40));
	q.Insert(Physics::BoundingBox(2, 30, 30));
	q.Insert(Physics::BoundingBox(2, 20, 20));
	q.Insert(Physics::BoundingBox(2, 10, 10));
	std::vector<Physics::BoundingBox const *> v;
	//q.RetrieveSelected(v,b);
}

int main(int argc, char ** argv) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	start();
	//test();


	_CrtDumpMemoryLeaks();
	return 0;
}