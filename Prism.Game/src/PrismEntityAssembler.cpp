#include "World/PrismEntityAssembler.h"

World::PrismEntityAssembler::PrismEntityAssembler(ECS::EntityManager &entityManager_, EntityFactory & factory_) : factory(factory_), EntityAssembler(entityManager_)
{
	//registerCreator(1, [&](ECS::EntityManager entityManager) -> int { return factory.createPlayer(entityManager); });
	registerCreator(1, [&]() -> int { return factory.createResourcePoint(entityManager_); });
	registerCreator(2, [&]() -> int { return factory.createResourcePoint(entityManager_); });
	registerCreator(3, [&]() -> int { return factory.createResourcePoint(entityManager_); });
	registerCreator(4, [&]() -> int { return factory.createPlayer(entityManager_); });
	registerCreator(5, [&]() -> int { return factory.createEnemy(entityManager_); });
	registerCreator(6, [&]() -> int { return factory.createWall(entityManager_); });
	registerCreator(7, [&]() -> int { return factory.createTower(entityManager_); });
	// TODO: This is an enemy spawnpoint
	registerCreator(8, [&]() -> int { return factory.createTower(entityManager_); });
}
