#pragma once
#include <iostream>
#include "CoreEngine.h"
#include "Window.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "InputManager.h"
#include "Key.h"
#include "Renderer/ForwardRenderer.h"
#include "Game.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "Context.h"
#include "StateMachine.h"
#include "Renderer/TestRenderer.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/AppearanceComponent.h"
#include "Renderer/Graphics/Models/Model.h";
#include "ECS/Systems/RenderSystem.h"
#include "ECS/SystemManager.h"

#define _CRTDBG_MAP_ALLOC

//QQQ Remove this main method
void test() {
	//State st;
	//CoreEngine ce = CoreEngine(st);
	//ce.CreateWindow("prism", 500, 500, 100, 100);
	//ce.Run();

	using namespace ECS;
	using namespace ECS::Components;
	using namespace ECS::Systems;



	EntityManager* et = new EntityManager();
	SystemManager sm;

	RenderSystem sys = RenderSystem(et);
	sm.registerSystem(sys);
	AppearanceComponent ac;
	ac.x = 3;
	ac.y = 4;
	ac.z = 1;
	Model* model = new Model(nullptr);
	ac.model = model;

	PositionComponent pc;
	pc.x = 10;
	pc.y = 20;

	et->createEntity(ac, pc);

	Context c;
	sys.update(c);



}

void start()
{
	Assimp::Importer importer;
	Window window;
	InputManager inputManager;
	window.init("Prism", 1920, 1080, 100, 100);
	window.createOpenGLContext(3, 2, true);


	while (!window.shouldClose()) {
		if (inputManager.isKeyPressed(Key::KEY_W)) {
			std::cout << "Key W is pressed!" << std::endl;
		}
		window.swapScreen();
	}
}

int main(int argc, char ** argv) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	test();



	_CrtDumpMemoryLeaks();
	return 0;
}