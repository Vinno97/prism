#pragma once
#include <memory>

#include "ECS/EntityManager.h"
#include "Enums/ResourceTypeEnum.h"

class EntityFactory {
public:
	~EntityFactory()
		= default;

	int createPlayer(ECS::EntityManager& entityManager);
	int createPlayer(int entity, ECS::EntityManager& entityManager);

	int createEnemy(ECS::EntityManager& entityManager);
	int createEnemy(int entity, ECS::EntityManager& entityManager);

	int createResourcePoint(ECS::EntityManager & entityManager, Enums::ResourceType type, int gatherRate, float value);
	int createResourcePoint(int entity, ECS::EntityManager & entityManager, Enums::ResourceType type, int gatherRate, float value);

	int createTower(ECS::EntityManager& entityManager);
	int createTower(int entity, ECS::EntityManager& entityManager);

	int createWall(ECS::EntityManager& entityManager);
	int createWall(int entity, ECS::EntityManager& entityManager);

	int createCliff(ECS::EntityManager& entityManager, int rotation = 0);
	int createCliff(int entity, ECS::EntityManager& entityManager, int rotation);

	int createMine(ECS::EntityManager& entityManager);
	int createMine(int entity, ECS::EntityManager& entityManager);

	int createScene(ECS::EntityManager & entityManager);

	int createProjectile(ECS::EntityManager & entityManager);

	int createScene(int entity, ECS::EntityManager & entityManager);
	
	int createEnemySpawn(ECS::EntityManager & entityManager, float spawnInterval, bool enabled);
	int createEnemySpawn(int entity, ECS::EntityManager & entityManager, float spawnInterval, bool enabled);


	int createFloor(ECS::EntityManager & entityManager);
	int createFloor(int entity, ECS::EntityManager & entityManager);

	int createResourceBlob(ECS::EntityManager & entityManager, Enums::ResourceType type, float value);
	int createResourceBlob(int entity, ECS::EntityManager & entityManager, Enums::ResourceType type, float value);
	
	int createCamera(ECS::EntityManager & entityManager);
	int createCameraPointer(ECS::EntityManager & entityManager);
private:
	//map<std::string, Model> modelCache; // TODO: Use this cache to cache the models to optimize memory usage.
};
