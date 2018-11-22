#include "World/Assemblers/EntityAssembler.h"

#include "World/Assemblers/AppearanceAssembler.h"
#include "World/Assemblers/PositionAssembler.h"

using namespace World;
using namespace World::Assemblers;

World::Assemblers::EntityAssembler::EntityAssembler()
{
	addAssembler(std::make_unique<AppearanceAssembler>(), PRIORITY_NORMAL);
	addAssembler(std::make_unique<PositionAssembler>(), PRIORITY_NORMAL);
}

void EntityAssembler::addAssembler(std::unique_ptr<BaseAssembler> &&assembler, int priority)
{
	assemblers.insert(std::pair<int, std::unique_ptr<BaseAssembler>>(priority, std::move(assembler)));
}

void EntityAssembler::addAssembler(std::unique_ptr<BaseAssembler> &&assembler)
{
	addAssembler(std::move(assembler), PRIORITY_NORMAL);
}

void World::Assemblers::EntityAssembler::assemble(int entity, const WorldObject & worldObject, ECS::EntityManager & entityManager) const
{
	for (const auto& assembler : assemblers) assembler.second->assemble(entity, worldObject, entityManager);
}

void World::Assemblers::EntityAssembler::disassemble(int entity, WorldObject & worldObject, const ECS::EntityManager & entityManager) const
{
	for (const auto& assembler : assemblers) assembler.second->disassemble(entity, worldObject, entityManager);
}
