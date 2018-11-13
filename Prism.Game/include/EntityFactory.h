#pragma once
#include <memory>

#include "ECS/EntityManager.h"

class EntityFactory {
public:
	EntityFactory();
	~EntityFactory();
	int createPlayer(ECS::EntityManager& entityManager);
	int createEnemy(ECS::EntityManager& entityManager);
	int createResourcePoint(ECS::EntityManager& entityManager);
	int createTower(ECS::EntityManager& entityManager);
	int createWall(ECS::EntityManager& entityManager);
	int createMine(ECS::EntityManager& entityManager);
	int createScene(ECS::EntityManager & entityManager);
	int createEnemySpawn(ECS::EntityManager & entityManager);
	int createFloor(ECS::EntityManager & entityManager);
private:
	//map<std::string, Model> modelCache; // TODO: Use this cache to cache the models to optimize memory usage.
};