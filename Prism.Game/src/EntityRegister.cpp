#include "EntityRegister.h"
	
EntityRegister::EntityRegister() {
}

void EntityRegister::RegisterPlayer(std::shared_ptr<EntityManager> entityManager)
{
	auto ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/bunny.obj");

	VelocityComponent velocity;
	PositionComponent position;
	BoundingBoxComponent boundingBox;
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
	

	entityManager->createEntity(velocity, position, drag, input, appearance, health, boundingBox);
	auto model2 = ml.loadModel("./res/bunny.obj");

	VelocityComponent velocity2;
	PositionComponent position2;
	BoundingBoxComponent boundingBox2;
	DragComponent drag2;
	HealthComponent health2;
	drag.force = 5.f;
	KeyboardInputComponent input2;

	AppearanceComponent appearance2;
	appearance2.translationZ = 1;
	appearance2.scaleX = 3;
	appearance2.scaleY = 3;
	appearance2.scaleZ = 3;
	appearance2.model = model2;


	entityManager->createEntity(velocity2, position2, drag2, input2, appearance2, health2, boundingBox2);
}

EntityRegister::~EntityRegister()
= default;