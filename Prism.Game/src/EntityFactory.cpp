#include "EntityFactory.h"

#include "ECS/Entity.h"
#include "ECS/Components/Component.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/SceneComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "ECS/Components/ResourceSpawnComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"

#include "Renderer/Graphics/Loader/ModelLoader.h"

using namespace ECS;
using namespace ECS::Components;

// TODO: Normaliseer alle modellen zodat ze goed gerendered kunnen worden met een scale van 1.

EntityFactory::EntityFactory() {

}

int EntityFactory::createPlayer(EntityManager& entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/player.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002f;
	appearance.scaleY = 0.002f;
	appearance.scaleZ = 0.002f;
	appearance.model = model;


	return entityManager.createEntity(appearance,
		VelocityComponent(),
		PositionComponent(),
		DragComponent(5.f),
		KeyboardInputComponent(),
		BoundingBoxComponent(0.2, 0.2),
		PlayerComponent()
	);
}

int EntityFactory::createEnemy(EntityManager& entityManager) {
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/uglyenemy.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002f;
	appearance.scaleY = 0.002f;
	appearance.scaleZ = 0.002f;
	appearance.model = model;

	return entityManager.createEntity(
		VelocityComponent(), 
		PositionComponent(), 
		DragComponent(5.f), 
		EnemyComponent(), 
		BoundingBoxComponent(0.2, 0.2),
		appearance);
}

int EntityFactory::createResourcePoint(EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/resource2.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002f;
	appearance.scaleY = 0.002f;
	appearance.scaleZ = 0.002f;
	appearance.model = model;
	return entityManager.createEntity(PositionComponent(), ResourceSpawnComponent(), appearance);

}

int EntityFactory::createTower(EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/tower-cross.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.005f;
	appearance.scaleY = 0.005f;
	appearance.scaleZ = 0.005f;
	appearance.model = model;
	return entityManager.createEntity(PositionComponent(), appearance);
}

int EntityFactory::createWall(EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/wall-cross.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.005f;
	appearance.scaleY = 0.005f;
	appearance.scaleZ = 0.005f;
	appearance.model = model;

	return entityManager.createEntity(PositionComponent(), appearance);
}

int EntityFactory::createMine(EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/uglyenemy.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.005f;
	appearance.scaleY = 0.005f;
	appearance.scaleZ = 0.005f;
	appearance.model = model;
	return entityManager.createEntity(PositionComponent(), appearance);
}

int EntityFactory::createScene(EntityManager & entityManager) {
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	std::shared_ptr<Model> model = ml.loadModel("./res/varyingPlane.obj");
	
	return entityManager.createEntity(SceneComponent());
}



EntityFactory::~EntityFactory()
= default;