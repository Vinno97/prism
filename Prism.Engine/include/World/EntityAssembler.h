#pragma once

#include <map>
#include "WorldObject.h"
#include "EntityConfigurators/EntityConfigurator.h"

namespace World {
	class EntityAssembler {
	public:
		EntityAssembler(ECS::EntityManager &entityManager);

		void registerCreator(int objectId, std::function<int(ECS::EntityManager)> fun);
		void registerCreator(int objectId, std::function<int()> fun);

		void registerConfigurator(std::function<void(int, const WorldObject&)> entityConfigurator);

		int assemble(const WorldObject& object) const;

	private:
		std::map<int, std::function<int()>> creators;
		std::vector<std::function<void(int, const WorldObject&)>> configurators;
		
		int createEntity(const WorldObject& object) const;
		void configureEntity(int entity, const WorldObject& object) const;

		ECS::EntityManager &entityManager;
	};
}
