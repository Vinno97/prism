#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class ProjectileAttackSystem : public System
		{
		public:
			ProjectileAttackSystem(EntityManager& entityManager);
			~ProjectileAttackSystem();

			void update(Context& context) override;
			std::unique_ptr<System> clone() override;
		private:
		};
	}
}