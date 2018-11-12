#include "EntityRegister.h"
	
EntityRegister::EntityRegister() {
}

void EntityRegister::RegisterPlayer(std::shared_ptr<EntityManager> entityManager)
{
	auto ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/bunny.obj");

	VelocityComponent velocity;
	PositionComponent position;
	DragComponent drag;
	HealthComponent health;
	drag.force = 5.f;
	KeyboardInputComponent input;

	
	AppearanceComponent appearance;
	appearance.translationZ = 1;
	appearance.scaleX = 3;
	appearance.scaleY = 3;
	appearance.scaleZ = 3;
	appearance.model = model;
	

	entityManager->createEntity(velocity, position, drag, input, appearance, health);
}

EntityRegister::~EntityRegister()
= default;