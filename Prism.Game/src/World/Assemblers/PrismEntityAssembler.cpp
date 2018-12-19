#include "World/Assemblers/PrismEntityAssembler.h"

#include "World/Assemblers/PlayerAssembler.h"
#include "World/Assemblers/EnemyAssembler.h"
#include "World/Assemblers/ResourceSpawnAssembler.h"
#include "World/Assemblers/TowerAssembler.h"
#include "World/Assemblers/WallAssembler.h"
#include "World/Assemblers/CliffFillerAssembler.h"
#include "World/Assemblers/CliffAssembler.h"
#include "World/Assemblers/CliffCornerAssembler.h"
#include "World/Assemblers/TreeAssembler.h"
#include "World/Assemblers/RockAssembler.h"
#include "World/Assemblers/EnemySpawnAssembler.h"
#include "World/Assemblers/MineAssembler.h"

using namespace World::Assemblers;

World::Assemblers::PrismEntityAssembler::PrismEntityAssembler() : EntityAssembler()
{
	addAssembler(std::make_unique<PlayerAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<EnemyAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<ResourceSpawnAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<TowerAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<WallAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<EnemySpawnAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<CliffAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<CliffCornerAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<TreeAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<RockAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<CliffFillerAssembler>(), PRIORITY_HIGH);
	addAssembler(std::make_unique<MineAssembler>(), PRIORITY_HIGH);
}
