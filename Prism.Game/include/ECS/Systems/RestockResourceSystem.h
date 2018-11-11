#pragma once

#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class RestockResourceSystem : public System
		{
		public:
			RestockResourceSystem(std::shared_ptr<EntityManager> entityManager);
			~RestockResourceSystem();
			void update(Context context) override;
		};
	}
}