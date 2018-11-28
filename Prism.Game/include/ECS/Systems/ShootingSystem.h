#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class ShootingSystem : public System
		{
		public:
			ShootingSystem(EntityManager& entityManager);
			~ShootingSystem();

			void update(Context& context) override;
			System* clone() override;
		};
	}
}

