#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;

namespace ECS {
	namespace Systems {
		class MotionSystem : public System
		{
		public:
			MotionSystem(EntityManager &entityManager);
			~MotionSystem();
			void update(Context context);
			System* clone() override;
		};
	}
}

