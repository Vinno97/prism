#include "World/Assemblers/PrismEntityAssembler.h"

#include "World/Assemblers/PlayerAssembler.h"
#include "World/Assemblers/EnemyAssembler.h"
#include "World/Assemblers/ResourceSpawnAssembler.h"
#include "World/Assemblers/TowerAssembler.h"
#include "World/Assemblers/WallAssembler.h"
#include "World/Assemblers/EnemySpawnAssembler.h"

using namespace World::Assemblers;

World::Assemblers::PrismEntityAssembler::PrismEntityAssembler() : EntityAssembler()
{
	addAssembler(std::make_unique<PlayerAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<EnemyAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<ResourceSpawnAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<TowerAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<WallAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<EnemySpawnAssembler>(), PRIORITY_HIGH);
}
