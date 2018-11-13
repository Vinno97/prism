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

#include "Renderer/Graphics/Loader/ModelLoader.h"

using namespace ECS;
using namespace ECS::Components;

// TODO: Normaliseer alle modellen zodat ze goed gerendered kunnen worden met een scale van 1.

int EntityFactory::createPlayer(EntityManager& entityManager) {
	return createPlayer(entityManager.createEntity(), entityManager);
}

int EntityFactory::createPlayer(int entity, EntityManager& entityManager) {
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/player.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002f;
	appearance.scaleY = 0.002f;
	appearance.scaleZ = 0.002f;
	appearance.model = std::move(model);


	entityManager.addComponentToEntity(entity, appearance);
	entityManager.addComponentToEntity(entity, VelocityComponent());
	entityManager.addComponentToEntity(entity, PositionComponent());
	entityManager.addComponentToEntity(entity, DragComponent(5.f));
	entityManager.addComponentToEntity(entity, KeyboardInputComponent());
	entityManager.addComponentToEntity(entity, PlayerComponent());
	return entity;
}

int EntityFactory::createEnemy(EntityManager& entityManager) {
	return createEnemy(entityManager.createEntity(), entityManager);
}

int EntityFactory::createEnemy(int entity, EntityManager& entityManager) {
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/uglyenemy.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002f;
	appearance.scaleY = 0.002f;
	appearance.scaleZ = 0.002f;
	appearance.model = std::move(model);

	entityManager.addComponentToEntity(entity, VelocityComponent());
	entityManager.addComponentToEntity(entity, PositionComponent());
	entityManager.addComponentToEntity(entity, DragComponent(5.f)); 
	entityManager.addComponentToEntity(entity, EnemyComponent());
	entityManager.addComponentToEntity(entity, appearance);
	
	return entity;
}

int EntityFactory::createResourcePoint(EntityManager & entityManager)
{
	return createResourcePoint(entityManager.createEntity(), entityManager);
}

int EntityFactory::createResourcePoint(int entity, EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/resource2.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002f;
	appearance.scaleY = 0.002f;
	appearance.scaleZ = 0.002f;
	appearance.model = std::move(model);

	entityManager.addComponentToEntity(entity, PositionComponent());
	entityManager.addComponentToEntity(entity, ResourceSpawnComponent());
	entityManager.addComponentToEntity(entity, appearance);
	return entity;
}
int EntityFactory::createTower(EntityManager & entityManager) {
	return createTower(entityManager.createEntity(), entityManager);
}


int EntityFactory::createTower(int entity, EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/tower-cross.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.005f;
	appearance.scaleY = 0.005f;
	appearance.scaleZ = 0.005f;
	appearance.model = std::move(model);

	entityManager.addComponentToEntity(entity, PositionComponent());
	entityManager.addComponentToEntity(entity, appearance);
	return entity;
}

int EntityFactory::createWall(EntityManager & entityManager) {
	return createWall(entityManager.createEntity(), entityManager);
}

int EntityFactory::createWall(int entity, EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/wall-cross.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.005f;
	appearance.scaleY = 0.005f;
	appearance.scaleZ = 0.005f;
	appearance.model = std::move(model);

	entityManager.addComponentToEntity(entity, PositionComponent());
	entityManager.addComponentToEntity(entity, appearance);
	return entity;
}

int EntityFactory::createMine(EntityManager & entityManager)
{
	return createMine(entityManager.createEntity(), entityManager);
}

int EntityFactory::createMine(int entity, EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/uglyenemy.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.005f;
	appearance.scaleY = 0.005f;
	appearance.scaleZ = 0.005f;
	appearance.model = std::move(model);
	return entityManager.createEntity(PositionComponent(), appearance);
	return entity;
}

int EntityFactory::createScene(EntityManager & entityManager) {
	return createScene(entityManager.createEntity(), entityManager);
}

int EntityFactory::createScene(int entity, EntityManager & entityManager) {
	entityManager.addComponentToEntity(entity, SceneComponent());
	return entity;
}
