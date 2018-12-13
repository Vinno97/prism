#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS
{
	namespace Systems
	{
		class HealthRegenerationSystem : public System
		{
		public:
			HealthRegenerationSystem(EntityManager& entityManager);
			~HealthRegenerationSystem();
			void update(Context& context) override;
		private:
			float regenTime = 2;
			float deltaTime = 0;
		};
	}
}
