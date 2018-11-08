#include "World/EntityAssembler.h"

namespace World {
	using namespace EntityConfigurators;

	//void EntityAssembler::registerCreator(int objectId, int(*fun)(void))
	//{
	//	this->creators[objectId] = fun;
	//}

	//void EntityAssembler::registerConfigurator(EntityConfigurators::EntityConfigurator& configurator)
	//{
	//	//this->configurators.push_back(*configurator.configure);
	//}

	EntityAssembler::EntityAssembler(ECS::EntityManager &entityManager_) : entityManager(entityManager_)
	{
	}

	//void EntityAssembler::registerCreator(int objectId, std::function<int(ECS::EntityManager)> fun)
	//{
	//	this->creators[objectId] = fun;
	//}

	void EntityAssembler::registerCreator(int objectId, std::function<int()> fun)
	{
		this->creators[objectId] = fun;
	}

	/*void EntityAssembler::registerConfigurator(std::unique_ptr<EntityConfigurators::EntityConfigurator> configurator)
	{
		this->configurators.push_back(configurator);
	}*/

	int EntityAssembler::assemble(WorldObject object) const {
		try {
			return creators.at(object.gid)();
		}
		catch (std::runtime_error&) {
			throw std::runtime_error("Could not assemble ");
		}
	}

	int EntityAssembler::createEntity(WorldObject object) const
	{
		return 0;
	}

	int EntityAssembler::createEntity(int entity, WorldObject object) const
	{
		return 0;
	}

}
