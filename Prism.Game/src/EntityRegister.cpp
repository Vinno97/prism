#include "EntityRegister.h"

#include "ECS/Entity.h"
#include "ECS/Components/Component.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"

#include "Renderer/Graphics/Loader/ModelLoader.h"

using namespace ECS;
using namespace ECS::Components;

EntityRegister::EntityRegister() {

}

int EntityRegister::createPlayer(EntityManager& entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	Model* model = ml.loadModel("./res/player.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002;
	appearance.scaleY = 0.002;
	appearance.scaleZ = 0.002;
	appearance.model = model;


	return entityManager.createEntity(appearance,
		VelocityComponent(),
		PositionComponent(),
		DragComponent(5.f),
		KeyboardInputComponent()
	);
}

int EntityRegister::createEnemy(EntityManager& entityManager) {
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	Model* model = ml.loadModel("./res/uglyenemy.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002;
	appearance.scaleY = 0.002;
	appearance.scaleZ = 0.002;
	appearance.model = model;

	return entityManager.createEntity(VelocityComponent(), PositionComponent(), DragComponent(5.f), appearance);

}

int EntityRegister::createResourcePoint(EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	Model* model = ml.loadModel("./res/resource2.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002;
	appearance.scaleY = 0.002;
	appearance.scaleZ = 0.002;
	appearance.model = model;
	return entityManager.createEntity(PositionComponent(), appearance);

}

int EntityRegister::createTower(EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	Model* model = ml.loadModel("./res/tower-cross.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.005;
	appearance.scaleY = 0.005;
	appearance.scaleZ = 0.005;
	appearance.model = model;
	return entityManager.createEntity(PositionComponent(), appearance);
}

int EntityRegister::createWall(EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	Model* model = ml.loadModel("./res/wall-cross.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.005;
	appearance.scaleY = 0.005;
	appearance.scaleZ = 0.005;
	appearance.model = model;

	return entityManager.createEntity(PositionComponent(), appearance);
}

int EntityRegister::createMine(EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	Model* model = ml.loadModel("./res/uglyenemy.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.005;
	appearance.scaleY = 0.005;
	appearance.scaleZ = 0.005;
	appearance.model = model;
	return entityManager.createEntity(PositionComponent(), appearance);
}

EntityRegister::~EntityRegister()
= default;