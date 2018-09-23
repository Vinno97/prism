#pragma once

#include <cstdlib>  
#include <crtdbg.h> 

#include <iostream>
#include "InputManager.h"
#include "Key.h"
#include "Window.h"

#include "ECS/EntityManager.h"
#include "ECS/Components/Component.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/MotionSystem.h"

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

	auto entities = entityManager.getAllEntities<VelocityComponent>();
	printf("All entities with %s\n", "VelocityComponent");
	for (auto entity : entities) {
		printf("Entity: %d; Velocity dX: %.3f, dY: %.3f\n", entity.id, entity.component->dx, entity.component->dy);
	}
}

void start() {
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
		for (auto &entity : entityManager.getAllEntities<VelocityComponent>()) {
			auto velocity = entity.component;
			auto position = entityManager.getComponent<PositionComponent>(entity.id);
			printf("Entity:\t\t%d \nPosition: \tX: %.2f, Y: %.2f\nVelocity:\tdX: %.2f, dY: %.2f\n\n", entity.id, position->x, position->y, velocity->dx, velocity->dy);
		}
	}
}

int main(int argc, char ** argv) {
	start();
	_CrtDumpMemoryLeaks();
	return 0;
}