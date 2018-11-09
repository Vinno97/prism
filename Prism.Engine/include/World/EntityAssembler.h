#pragma once

#include <map>
#include "WorldObject.h"
#include "EntityConfigurators/EntityConfigurator.h"

namespace World {
	class EntityAssembler {
	public:
		EntityAssembler(ECS::EntityManager &entityManager);

		//void registerCreator(int objectId, int(*fun)(void));
		//void registerCreator(int objectId, std::function<int()>);
		void registerCreator(int objectId, std::function<int(ECS::EntityManager)> fun);
		void registerCreator(int objectId, std::function<int()> fun);
		//template<typename T, typename = std::enable_if_t<std::is_base_of_v<EntityConfigurators::EntityConfigurator, T>>>
		//void registerConfigurator(EntityConfigurators::EntityConfigurator& entityConfigurator);

		void registerConfigurator(std::function<void(int, const WorldObject&)> entityConfigurator);
		//void registerConfigurator(std::unique_ptr<EntityConfigurators::EntityConfigurator> entityConfigurator);

		int assemble(const WorldObject& object) const;

	private:
		std::map<int, std::function<int()>> creators;
		std::vector<std::function<void(int, const WorldObject&)>> configurators;

		//std::vector<void(*)(int, WorldObject&, ECS::EntityManager&)> configurators;
		//std::vector<EntityConfigurators::EntityConfigurator*> configurators;

		//std::vector<std::unique_ptr<EntityConfigurators::EntityConfigurator>> configurators;
		
		int createEntity(const WorldObject& object) const;
		void configureEntity(int entity, const WorldObject& object) const;

		ECS::EntityManager &entityManager;
	};
}
