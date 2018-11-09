#include "World/EntityAssembler.h"

#include "World/EntityConfigurators/AppearanceConfigurator.h"
#include "World/EntityConfigurators/PositionConfigurator.h"

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
		registerConfigurator([&](int entity, const WorldObject &object) -> void { AppearanceConfigurator().configure(entity, object, entityManager_); });
		registerConfigurator([&](int entity, const WorldObject &object) -> void { PositionConfigurator().configure(entity, object, entityManager_); });
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

	void EntityAssembler::registerConfigurator(std::function<void(int, const WorldObject&)> configurator)
	{
		this->configurators.push_back(configurator);
	}

	int EntityAssembler::assemble(const WorldObject& object) const {
		auto entity = createEntity(object);
		configureEntity(entity, object);
		return entity;
	}

	int EntityAssembler::createEntity(const WorldObject& object) const
	{
		try {
			return creators.at(object.gid)();
		}
		catch (std::runtime_error&) {
			throw std::runtime_error("Could not assemble ");
		}
	}

	void EntityAssembler::configureEntity(int entity, const WorldObject& object) const
	{
		for (const auto& configurator : configurators) {
			configurator(entity, object);
		}
	}

}
