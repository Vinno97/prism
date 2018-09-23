#pragma once
#include "Window.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"

#include "ECS/Components/Component.h"


#include <cstdlib>  
#include <crtdbg.h> 

// This function makes sure all objects are cleared from the stack before the memory gets dumped.

void start() {
	using namespace ECS;
	using namespace ECS::Components;

	EntityManager entityManager;

	PositionComponent position;
	position.x = 1;
	position.y = 5;

	VelocityComponent velocity;
	velocity.dx = 1.5f;
	velocity.dy = .6f;

	//int entity = entityManager.createEntity(position, velocity);
	int entity = entityManager.createEntity(velocity);
	entityManager.addComponentToEntity(entity, position);

	//entityManager.removeComponentFromEntity<PositionComponent>(entity);

	auto c = entityManager.getComponent<PositionComponent>(entity);
	printf("Position: X: %d, Y: %d\n", c->x, c->y);

	auto entities = entityManager.getAllEntities<VelocityComponent>();
	printf("All entities with %s\n", "VelocityComponent");
	for (auto entity : entities) {
		printf("Entity: %d; Velocity dX: %.3f, dY: %.3f\n", entity.id, entity.component->dx, entity.component->dy);
	}



	/*SDLFacade::Window window;
	window.init("Prism", 1280, 720, 100, 100);
	window.createOpenGLContext(4, 1, true);
	while (true) {
	}*/
}

//QQQ Remove this main method
int main(int argc, char ** argv) {
	start();
	_CrtDumpMemoryLeaks();
	return 0;
}