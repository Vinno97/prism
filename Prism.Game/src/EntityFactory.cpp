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
#include <World/TerrainGenerator.h>
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
	appearance.model = std::move(model);
	appearance.color = Math::Vector3f{ 1.0f, 0.5f, 0.5f };

	return entityManager.createEntity(appearance,
		VelocityComponent(),
		PositionComponent(),
		DragComponent(5.f),
		KeyboardInputComponent(),
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
	appearance.model = std::move(model);

	return entityManager.createEntity(VelocityComponent(), PositionComponent(), DragComponent(5.f), EnemyComponent(), appearance);

}

int EntityFactory::createResourcePoint(EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/resource2.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002f;
	appearance.scaleY = 0.002f;
	appearance.scaleZ = 0.002f;
	appearance.model = std::move(model);
	appearance.color = Math::Vector3f{ 0.6f, 0.6f, 1.0f };
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
	appearance.model = std::move(model);
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
	appearance.model = std::move(model);

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
	appearance.model = std::move(model);
	return entityManager.createEntity(PositionComponent(), appearance);
}

int EntityFactory::createScene(EntityManager & entityManager) {
	return entityManager.createEntity(SceneComponent());
}

int EntityFactory::createFloor(ECS::EntityManager & entityManager)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = World::TerrainGenerator().generateTerrain(100, 100);

	AppearanceComponent appearance;
	appearance.translationX -= 6.25;
	appearance.translationZ -= 6.25;

	appearance.scaleX = 0.25;
	appearance.scaleY = 0.25;
	appearance.scaleZ = 0.25;

	appearance.color = Math::Vector3f{ 0.90f, 0.90f, 0.90f };
	appearance.model = std::move(model);
	appearance.color = Math::Vector3f{ 0.8f, 0.8f, 0.8f };
	PositionComponent positionComponent;
	return entityManager.createEntity(positionComponent, appearance);
}



EntityFactory::~EntityFactory()
= default;