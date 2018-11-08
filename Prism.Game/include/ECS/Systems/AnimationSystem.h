#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class AnimationSystem : public System
		{
		public:
			AnimationSystem(std::shared_ptr<EntityManager> entityManager);
			~AnimationSystem();
			void update(Context context) override;

		private:
			long double absoluteTime = 0;
		};
	}
}