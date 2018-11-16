#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "../../Prism.Engine/include/ECS/Systems/CheatSystem.h"



namespace ECS {
	namespace Systems {
		class KeyboardInputSystem : public System
		{
		public:
			KeyboardInputSystem(EntityManager &entityManager);
			~KeyboardInputSystem();
			void update(Context context) override;
			System* clone() override;
		};
	}
}