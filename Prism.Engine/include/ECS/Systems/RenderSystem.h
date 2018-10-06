#pragma once

#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class RenderSystem : public System
		{
		public:
			RenderSystem(EntityManager* entityManager);
			~RenderSystem();
			void update(Context context) override;
		};
	}
}