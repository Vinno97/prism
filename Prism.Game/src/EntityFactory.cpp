#include "EntityFactory.h"

#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/BulletComponent.h"
#include "ECS/Components/CameraComponent.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/DynamicComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/EnemySpawnComponent.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "ECS/Components/MineComponent.h"
#include "ECS/Components/TargetComponent.h"
#include "ECS/Components/MousePointerComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/ProjectileAttackComponent.h"
#include "ECS/Components/ResourceBlobComponent.h"
#include "ECS/Components/ResourceGatherComponent.h"
#include "ECS/Components/ResourceSpawnComponent.h"
#include "ECS/Components/SceneComponent.h"
#include "ECS/Components/ShootingComponent.h"
#include "ECS/Components/TowerComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/WallComponent.h"
#include "ECS/Components/PlacableComponent.h"
#include "ECS/EntityBuilder.h"
#include "Renderer/Camera.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "World/TerrainGenerator.h"

using namespace ECS;
using namespace ECS::Components;

// TODO: Normaliseer alle modellen zodat øze goed gerendered kunnen worden met
// een scale van 1.

unsigned EntityFactory::createPlayer(EntityManager& entityManager) const
{
	return createPlayer(entityManager.createEntity(), entityManager);
}

unsigned EntityFactory::createPlayer(unsigned entity, EntityManager& entityManager) const
{
	Renderer::Graphics::Loader::ModelLoader ml;
	auto model = ml.loadModel("./res/player.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002f;
	appearance.scaleY = 0.002f;
	appearance.scaleZ = 0.002f;
	appearance.model = std::move(model);
	appearance.color = Math::Vector3f{1.0f, 0.5f, 0.5f};

	return EntityBuilder(entityManager, entity)
	       .addComponent<VelocityComponent>()
	       .addComponent<PositionComponent>()
	       .addComponent<KeyboardInputComponent>()
	       .addComponent<PlayerComponent>()
	       .addComponent<InventoryComponent>()
	       .addComponent<ResourceGatherComponent>()
	       .addComponent<ShootingComponent>()
	       .addComponent<DynamicComponent>()
	       .addComponent<HealthComponent>(100)
	       .addComponent<DragComponent>(5.f)
	       .addComponent<BoundingBoxComponent>(.3, .3)
		   .addComponent<PlacableComponent>()
	       .addComponent(appearance)
	       .getEntity();
}

unsigned EntityFactory::createEnemy(EntityManager& entityManager) const
{
	return createEnemy(entityManager.createEntity(), entityManager);
}

unsigned EntityFactory::createEnemy(unsigned entity, EntityManager& entityManager) const
{
	Renderer::Graphics::Loader::ModelLoader ml;
	auto model = ml.loadModel("./res/uglyenemy.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002f;
	appearance.scaleY = 0.002f;
	appearance.scaleZ = 0.002f;
	appearance.model = std::move(model);

	return EntityBuilder(entityManager, entity)
	       .addComponent<VelocityComponent>()
	       .addComponent<PositionComponent>()
	       .addComponent<EnemyComponent>()
	       .addComponent<DynamicComponent>()
	       .addComponent<HealthComponent>(100)
	       .addComponent<DragComponent>(5.f)
	       .addComponent<BoundingBoxComponent>(.4, .4)
		   .addComponent<PlacableComponent>()
	       .addComponent(appearance)
	       .getEntity();
}

unsigned EntityFactory::createResourcePoint(EntityManager& entityManager,
                                            Enums::ResourceType type, int gatherRate,
                                            float value) const
{
	return createResourcePoint(entityManager.createEntity(), entityManager, type,
	                           gatherRate, value);
}

unsigned EntityFactory::createResourcePoint(unsigned entity, EntityManager& entityManager,
                                            Enums::ResourceType type, int gatherRate,
                                            float value) const
{
	Renderer::Graphics::Loader::ModelLoader ml;
	auto model = ml.loadModel("./res/resource2.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.002f;
	appearance.scaleY = 0.002f;
	appearance.scaleZ = 0.002f;
	appearance.model = std::move(model);

	if (type == Enums::ResourceType::BLUE)
	{
		appearance.color = Math::Vector3f{0.6f, 0.6f, 1.0f};
	}
	if (type == Enums::ResourceType::RED)
	{
		appearance.color = Math::Vector3f{1.0f, 0.6f, 0.6f};
	}
	if (type == Enums::ResourceType::GREEN)
	{
		appearance.color = Math::Vector3f{0.6f, 1.0f, 0.6f};
	}
	return EntityBuilder(entityManager, entity)
	       .addComponent<PositionComponent>()
	       .addComponent<ResourceSpawnComponent>(gatherRate, type, value)
	       .addComponent(appearance)
	       .getEntity();
}

unsigned EntityFactory::createTower(EntityManager& entityManager) const
{
	return createTower(entityManager.createEntity(), entityManager);
}

unsigned EntityFactory::createTower(unsigned entity, EntityManager& entityManager) const
{
	Renderer::Graphics::Loader::ModelLoader ml;
	auto model = ml.loadModel("./res/wall.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.5f;
	appearance.scaleY = 0.5f;
	appearance.scaleZ = 0.5f;
	appearance.model = std::move(model);

	return EntityBuilder(entityManager, entity)
	       .addComponent<TowerComponent>()
	       .addComponent<PositionComponent>()
	       .addComponent<BoundingBoxComponent>(1.0, 1.0)
		   .addComponent<PlacableComponent>()
	       .addComponent(appearance)
	       .getEntity();
}

unsigned EntityFactory::createWall(EntityManager& entityManager) const
{
	return createWall(entityManager.createEntity(), entityManager);
}

unsigned EntityFactory::createWall(unsigned entity, EntityManager& entityManager) const
{
	Renderer::Graphics::Loader::ModelLoader ml;
	auto model = ml.loadModel("./res/wall.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.5f;
	appearance.scaleY = 0.5f;
	appearance.scaleZ = 0.5f;
	appearance.model = std::move(model);
	appearance.color = Math::Vector3f{0.9f, 0.9f, 0.9f};

	return EntityBuilder(entityManager, entity)
	       .addComponent<WallComponent>()
	       .addComponent<PositionComponent>()
	       .addComponent<BoundingBoxComponent>(1.0, 1.0)
		   .addComponent<PlacableComponent>()
	       .addComponent(appearance)
	       .getEntity();
}

unsigned EntityFactory::createMine(EntityManager& entityManager) const
{
	return createMine(entityManager.createEntity(), entityManager);
}

unsigned EntityFactory::createMine(unsigned entity, EntityManager& entityManager) const
{
	Renderer::Graphics::Loader::ModelLoader ml;
	auto model = ml.loadModel("./res/uglyenemy.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.005f;
	appearance.scaleY = 0.005f;
	appearance.scaleZ = 0.005f;
	appearance.model = std::move(model);

	return EntityBuilder(entityManager, entity)
	       .addComponent<MineComponent>()
	       .addComponent<PositionComponent>()
		   .addComponent<BoundingBoxComponent>(1.0, 1.0)
	       .addComponent<ResourceGatherComponent>()
		   .addComponent<PlacableComponent>()
	       .addComponent(appearance)
	       .getEntity();
}

unsigned EntityFactory::createScene(EntityManager& entityManager) const
{
	return createScene(entityManager.createEntity(), entityManager);
}

unsigned EntityFactory::createScene(unsigned entity, EntityManager& entityManager)
{
	entityManager.addComponentToEntity<SceneComponent>(entity);
	return entity;
}

unsigned EntityFactory::createProjectile(EntityManager& entityManager) const
{
	return createProjectile(entityManager.createEntity(), entityManager);
}

unsigned EntityFactory::createProjectile(unsigned entity, EntityManager& entityManager) const
{
	Renderer::Graphics::Loader::ModelLoader ml;
	auto model = ml.loadModel("./res/projectile.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.1f;
	appearance.scaleY = 0.1f;
	appearance.scaleZ = 0.1f;
	appearance.model = std::move(model);

	return EntityBuilder(entityManager, entity)
	       .addComponent<VelocityComponent>()
	       .addComponent<PositionComponent>()
	       .addComponent<BulletComponent>()
	       .addComponent<HealthComponent>(15)
	       .addComponent<BoundingBoxComponent>(0.1, 0.1)
	       .addComponent<ProjectileAttackComponent>()
	       .addComponent<DynamicComponent>()
	       .addComponent(appearance)
	       .getEntity();
}

unsigned EntityFactory::createFloor(ECS::EntityManager& entityManager) const
{
	return createFloor(entityManager.createEntity(), entityManager);
}

unsigned EntityFactory::createFloor(unsigned entity, EntityManager& entityManager) const
{
	const int width{150};
	const int height{150};
	const float scale{0.5};

	Renderer::Graphics::Loader::ModelLoader ml;
	auto model =
		World::TerrainGenerator().generateTerrain(width / scale, height / scale);

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
	appearance.color = Math::Vector3f{0.8f, 0.8f, 0.82f};

	return EntityBuilder(entityManager, entity)
	       .addComponent<PositionComponent>()
	       .addComponent(appearance)
	       .getEntity();
}

unsigned EntityFactory::createResourceBlob(ECS::EntityManager& entityManager,
                                           Enums::ResourceType type, float value) const
{
	return createResourceBlob(entityManager.createEntity(), entityManager, type,
	                          value);
}

unsigned EntityFactory::createResourceBlob(unsigned entity,
                                           ECS::EntityManager& entityManager,
                                           Enums::ResourceType type, float value) const
{
	Renderer::Graphics::Loader::ModelLoader ml;
	auto model = ml.loadModel("./res/blob.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.05f;
	appearance.scaleY = 0.05f;
	appearance.scaleZ = 0.05f;
	appearance.translationY = 0.2f;
	appearance.model = std::move(model);

	if (type == Enums::ResourceType::BLUE)
	{
		appearance.color = Math::Vector3f{0.6f, 0.6f, 1.0f};
	}
	if (type == Enums::ResourceType::RED)
	{
		appearance.color = Math::Vector3f{1.0f, 0.6f, 0.6f};
	}
	if (type == Enums::ResourceType::GREEN)
	{
		appearance.color = Math::Vector3f{0.6f, 1.0f, 0.6f};
	}

	ResourceBlobComponent resource = ResourceBlobComponent(value, type);

	return EntityBuilder(entityManager, entity)
	       .addComponent<PositionComponent>()
	       .addComponent<VelocityComponent>()
	       .addComponent<DragComponent>()
           .addComponent<TargetComponent>()
	       .addComponent(resource)
	       .addComponent(appearance)
	       .getEntity();
}

unsigned EntityFactory::createCameraPointer(ECS::EntityManager& entityManager)
{
	return entityManager.createEntity(MousePointerComponent(),
	                                  PositionComponent());
}

unsigned EntityFactory::createEnemySpawn(ECS::EntityManager& entityManager,
                                         float spawnInterval, bool enabled) const
{
	return createEnemySpawn(entityManager.createEntity(), entityManager,
	                        spawnInterval, enabled);
}

unsigned EntityFactory::createEnemySpawn(unsigned entity,
                                         ECS::EntityManager& entityManager,
                                         float spawnInterval, bool enabled) const
{
	Renderer::Graphics::Loader::ModelLoader ml;
	auto model = ml.loadModel("./res/spawner.obj");

	AppearanceComponent appearance;
	appearance.scaleX = 0.15f;
	appearance.scaleY = 0.15f;
	appearance.scaleZ = 0.15f;
	appearance.color = Math::Vector3f{0.22, 0.22, 0.22};

	PositionComponent position;
	position.y = 0;

	appearance.model = std::move(model);
	EnemySpawnComponent spawnComponent =
		EnemySpawnComponent{spawnInterval, 0.f, enabled};

	return EntityBuilder(entityManager, entity)
	       .addComponent(position)
	       .addComponent(spawnComponent)
	       .addComponent(appearance)
	       .getEntity();
}

unsigned EntityFactory::createCamera(ECS::EntityManager& entityManager)
{
	Renderer::Camera camera;

	camera.move(0, 2.f, 3.f);
	camera.rotate(-35.f, 0.f, 0.f);

	CameraComponent component;
	component.camera = camera;
	return entityManager.createEntity(component);
}
