#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class AimingSystem : public System
		{
		public:
			AimingSystem(EntityManager& entityManager);
			~AimingSystem();

			void update(Context& context) override;
			std::unique_ptr<System> clone() override;
		private:

		};
	}
}