#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class MotionSystem : public System
		{
		public:
			MotionSystem(EntityManager &entityManager);
			~MotionSystem();
			void update(Context& context);
		};
	}
}
