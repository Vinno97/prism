#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class GameOverSystem : public System {
		public:
			GameOverSystem(EntityManager &entityManager);
			~GameOverSystem();
			System* clone() override;
			void update(Context& context) override;
		};
	}
}

