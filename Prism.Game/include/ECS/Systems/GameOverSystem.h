#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class GameOverSystem : public System {
		public:
			GameOverSystem(EntityManager &entityManager);
			~GameOverSystem();
			void update(Context& context) override;
		private:
			bool health_sound_is_playing = false;
		};
	}
}

