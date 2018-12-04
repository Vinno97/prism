#pragma once

#include <PathFinding/PathFindingStrategy.h>
#include <PathFinding/LinearPathFindingStrategy.h>
#include <PathFinding/Strategies.h>
#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class PathFindingSystem : public System {
		public:
			PathFindingSystem(EntityManager &entityManager);

			~PathFindingSystem() override;

			void update(Context &context) override;

		private:
			std::unordered_map<PathFinding::Strategies::PathFindingStrategy, std::unique_ptr<PathFinding::PathFindingStrategy>> strategies;
			PathFinding::LinearPathFinding linearPathFinding;
		};
	}
}