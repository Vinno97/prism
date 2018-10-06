#pragma once

#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class RenderSystem : public System
		{
		public:
			RenderSystem(std::shared_ptr<EntityManager> entityManager);
			~RenderSystem();
			void update(Context context) override;
		};
	}
}