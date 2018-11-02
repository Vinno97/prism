#include "EntityRegister.h"

///<sumary>


EntityRegister::EntityRegister() {
}

void EntityRegister::RegisterPlayer(std::shared_ptr<EntityManager> entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	Model* model = ml.loadModel("./res/bunny.obj");

	VelocityComponent velocity;
	PositionComponent position;
	DragComponent drag;
	drag.force = 5.f;
	KeyboardInputComponent input;

	
	AppearanceComponent appearance;
	appearance.translationZ = 1;
	appearance.scaleX = 3;
	appearance.scaleY = 3;
	appearance.scaleZ = 3;
	appearance.model = model;
	

	entityManager->createEntity(velocity, position, drag, input, appearance);
}

EntityRegister::~EntityRegister()
= default;