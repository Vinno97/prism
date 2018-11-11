#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class AnimationSystem : public System
		{
		public:
			AnimationSystem(EntityManager& entityManager);
			~AnimationSystem();
			void update(Context context) override;
			System* clone() override;
		private:
			long double absoluteTime = 0;
		};
	}
}