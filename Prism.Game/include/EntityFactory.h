#pragma once
#include <memory>

#include "ECS/EntityManager.h"
#include "Enums/ResourceTypeEnum.h"

class EntityFactory {
public:
	EntityFactory();
	~EntityFactory();
	int createPlayer(ECS::EntityManager& entityManager);
	int createEnemy(ECS::EntityManager& entityManager);
	int createResourcePoint(ECS::EntityManager & entityManager, Enums::ResourceType type, int gatherRate, float value);
	int createTower(ECS::EntityManager& entityManager);
	int createWall(ECS::EntityManager& entityManager);
	int createMine(ECS::EntityManager& entityManager);
	int createScene(ECS::EntityManager & entityManager);
	int createFloor(ECS::EntityManager & entityManager);
	int CreateBlob(ECS::EntityManager & entityManager, Enums::ResourceType type, float value);
private:
	//map<std::string, Model> modelCache; // TODO: Use this cache to cache the models to optimize memory usage.
};