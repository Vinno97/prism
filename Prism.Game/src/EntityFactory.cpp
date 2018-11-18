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
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/ResourceGatherComponent.h"
#include "ECS/Components/ResourceBlobComponent.h"
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
		PlayerComponent(),
		InventoryComponent(),
		ResourceGatherComponent()
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

int EntityFactory::createResourcePoint(EntityManager & entityManager, Enums::ResourceType type, int gatherRate, float value)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/resource2.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002f;
	appearance.scaleY = 0.002f;
	appearance.scaleZ = 0.002f;
	appearance.model = std::move(model);

	if (type == Enums::ResourceType::BLUE) {
		appearance.color = Math::Vector3f{ 0.6f, 0.6f, 1.0f };
	}
	if (type == Enums::ResourceType::RED) {
		appearance.color = Math::Vector3f{ 1.0f, 0.6f, 0.6f };
	}
	if (type == Enums::ResourceType::GREEN) {
		appearance.color = Math::Vector3f{ 0.6f, 1.0f, 0.6f };
	}
	return entityManager.createEntity(PositionComponent(), ResourceSpawnComponent(gatherRate, type, value), appearance);

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

	appearance.scaleX = 0.125;
	appearance.scaleY = 0.125;
	appearance.scaleZ = 0.125;

	appearance.model = std::move(model);
	appearance.color = Math::Vector3f{ 0.87f, 0.87f, 0.87f };
	PositionComponent positionComponent;
	return entityManager.createEntity(positionComponent, appearance);
}

int EntityFactory::CreateBlob(ECS::EntityManager & entityManager, Enums::ResourceType type, float value)
{
	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	auto model = ml.loadModel("./res/blob.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.05f;
	appearance.scaleY = 0.05f;
	appearance.scaleZ = 0.05f;
	appearance.translationY = 0.2f;
	appearance.model = std::move(model);

	if (type == Enums::ResourceType::BLUE) {
		appearance.color = Math::Vector3f{ 0.6f, 0.6f, 1.0f };
	}
	if (type == Enums::ResourceType::RED) {
		appearance.color = Math::Vector3f{ 1.0f, 0.6f, 0.6f };
	}
	if (type == Enums::ResourceType::GREEN) {
		appearance.color = Math::Vector3f{ 0.6f, 1.0f, 0.6f };
	}

	ResourceBlobComponent resource = ResourceBlobComponent(value , type);

	return entityManager.createEntity(appearance, PositionComponent(), VelocityComponent(), resource, DragComponent());
}



EntityFactory::~EntityFactory()
= default;