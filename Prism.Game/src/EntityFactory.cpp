#include "EntityFactory.h"

#include "ECS/Entity.h"
#include "ECS/Components/Component.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/WallComponent.h"
#include "ECS/Components/MineComponent.h"
#include "ECS/Components/SceneComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/TowerComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "ECS/Components/ResourceSpawnComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include <World/TerrainGenerator.h>
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
	appearance.color = Math::Vector3f{ 1.0f, 0.5f, 0.5f };


	entityManager.addComponentToEntity(entity, appearance);
	entityManager.addComponentToEntity(entity, VelocityComponent());
	entityManager.addComponentToEntity(entity, PositionComponent());
	entityManager.addComponentToEntity(entity, DragComponent(5.f));
	entityManager.addComponentToEntity(entity, KeyboardInputComponent());
	entityManager.addComponentToEntity(entity, PlayerComponent());
	entityManager.addComponentToEntity(entity, BoundingBoxComponent(.3,.3));
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
	entityManager.addComponentToEntity(entity, BoundingBoxComponent(.4, .4));
	
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
	appearance.color = Math::Vector3f{ 0.6f, 0.6f, 1.0f };

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

	entityManager.addComponentToEntity(entity, TowerComponent());
	entityManager.addComponentToEntity(entity, PositionComponent());
	entityManager.addComponentToEntity(entity, appearance);
	entityManager.addComponentToEntity(entity, BoundingBoxComponent(1, 1));
	return entity;
}

int EntityFactory::createWall(EntityManager & entityManager) {
	return createWall(entityManager.createEntity(), entityManager);
}

int EntityFactory::createWall(int entity, EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/wall.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.5f;
	appearance.scaleY = 0.5f;
	appearance.scaleZ = 0.5f;
	appearance.model = std::move(model);
	appearance.color = Math::Vector3f{ 0.9f, 0.9f, 0.9f };
	entityManager.addComponentToEntity(entity, WallComponent());
	entityManager.addComponentToEntity(entity, PositionComponent());
	entityManager.addComponentToEntity(entity, appearance);
	entityManager.addComponentToEntity(entity, BoundingBoxComponent(1, 1));
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

	entityManager.addComponentToEntity(entity, MineComponent());
	entityManager.addComponentToEntity(entity, PositionComponent());
	entityManager.addComponentToEntity(entity, appearance);
	return entity;
}

int EntityFactory::createScene(EntityManager & entityManager) {
	return createScene(entityManager.createEntity(), entityManager);
}

int EntityFactory::createScene(int entity, EntityManager & entityManager) {
	entityManager.addComponentToEntity(entity, SceneComponent());
	return entity;
}

int EntityFactory::createFloor(ECS::EntityManager & entityManager)
{
    return createFloor(entityManager.createEntity(), entityManager);
}

int EntityFactory::createFloor(int entity, EntityManager & entityManager) {
	int width = 150;
	int height = 150;
	float scale = 0.5;

	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = World::TerrainGenerator().generateTerrain(width / scale, height / scale);

	AppearanceComponent appearance;
	appearance.translationX -= 6.25;
	appearance.translationZ -= 6.25;

	appearance.scaleX = scale;
	appearance.scaleY = scale / 3;
	appearance.scaleZ = scale;

	appearance.translationX = -width / 2;
	appearance.translationZ = -height / 2;
	appearance.translationY = -scale / 15;

	appearance.model = std::move(model);
	appearance.color = Math::Vector3f{ 0.65f, 0.65f, 0.8f };
	
	entityManager.addComponentToEntity(entity, PositionComponent());
	entityManager.addComponentToEntity(entity, appearance);
	return entity;
}
