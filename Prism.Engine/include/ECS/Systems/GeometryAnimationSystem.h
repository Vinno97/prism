#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class GeometryAnimationSystem : public System {
		public:
			GeometryAnimationSystem(ECS::EntityManager &entityManager);
			~GeometryAnimationSystem() = default;
			void update(Context& context) override;
		};
	}
}



