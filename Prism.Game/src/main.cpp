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
#include "Renderer/TestRenderer.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/MotionSystem.h"

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
// This function makes sure all objects are cleared from the stack before the memory gets dumped.
using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;

void setUpEntities(EntityManager& entityManager) {
	PositionComponent position;
	VelocityComponent velocity;
	KeyboardInputComponent input;
	DragComponent drag;

	drag.force = 0.1;

	int entity = entityManager.createEntity(position, velocity, input, drag);

	auto c = entityManager.getComponent<PositionComponent>(entity);
	printf("Position: X: %.2f, Y: %.2f\n", c->x, c->y);

	auto entities = entityManager.getAllEntitiesWithComponent<VelocityComponent>();
	printf("All entities with %s\n", "VelocityComponent");
	for (auto entity : entities) {
		printf("Entity: %d; Velocity dX: %.3f, dY: %.3f\n", entity.id, entity.component->dx, entity.component->dy);
	}
}

void startmove() {
	Window window;
	InputManager inputManager;
	Context context;
	window.init("Prism", 1280, 720, 100, 100);
	window.createOpenGLContext(4, 1, true);
	context.inputManager = &inputManager;

	EntityManager entityManager;
	setUpEntities(entityManager);

	KeyboardInputSystem input = KeyboardInputSystem(&entityManager);
	MotionSystem motion = MotionSystem(&entityManager);

	while (!window.shouldClose()) {
		input.update(context);
		motion.update(context);
		for (auto &entity : entityManager.getAllEntitiesWithComponent<VelocityComponent>()) {
			auto velocity = entity.component;
			auto position = entityManager.getComponent<PositionComponent>(entity.id);
			printf("Entity:\t\t%d \nPosition: \tX: %.2f, Y: %.2f\nVelocity:\tdX: %.2f, dY: %.2f\n\n", entity.id, position->x, position->y, velocity->dx, velocity->dy);
		}
	}
}

int main(int argc, char ** argv) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	test();
	_CrtDumpMemoryLeaks();
	return 0;
}