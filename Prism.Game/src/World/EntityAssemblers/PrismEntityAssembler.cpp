#include "World/Assemblers/PrismEntityAssembler.h"

#include "World/Assemblers/PlayerAssembler.h"
#include "World/Assemblers/EnemyAssembler.h"
#include "World/Assemblers/ResourceSpawnAssembler.h"
#include "World/Assemblers/TowerAssembler.h"
#include "World/Assemblers/WallAssembler.h"

using namespace World::Assemblers;

//PrismEntityAssembler::PrismEntityAssembler()
//{
//
//	//registerCreator(1, [&](ECS::EntityManager entityManager) -> int { return factory.createPlayer(entityManager); });
//	//registerCreator(1, [&]() -> int { return factory.createResourcePoint(entityManager_); });
//	//registerCreator(2, [&]() -> int { return factory.createResourcePoint(entityManager_); });
//	//registerCreator(3, [&]() -> int { return factory.createResourcePoint(entityManager_); });
//	//registerCreator(4, [&]() -> int { return factory.createPlayer(entityManager_); });
//	//registerCreator(5, [&]() -> int { return factory.createEnemy(entityManager_); });
//	//registerCreator(6, [&]() -> int { return factory.createWall(entityManager_); });
//	//registerCreator(7, [&]() -> int { return factory.createTower(entityManager_); });
//	//// TODO: This is an enemy spawnpoint
//	//registerCreator(8, [&]() -> int { return factory.createTower(entityManager_); });
//
//	
//}

World::Assemblers::PrismEntityAssembler::PrismEntityAssembler() : EntityAssembler()
{
	addAssembler(std::make_unique<PlayerAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<EnemyAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<ResourceSpawnAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<TowerAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<WallAssembler>(), PRIORITY_HIGH);
}
