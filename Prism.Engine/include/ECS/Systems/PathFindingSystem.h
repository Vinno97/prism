#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class PathFindingSystem : public System
		{
		public:
			PathFindingSystem(EntityManager &entityManager);
			~PathFindingSystem();
			void update(Context context);
			System* clone() override;
		};
	}
}
