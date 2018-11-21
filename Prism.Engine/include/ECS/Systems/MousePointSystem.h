#pragma once
#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "ECS/Components/MousePointerComponent.h"

namespace ECS {
	namespace Systems {
		class MousePointSystem : public System
		{
		public:
			MousePointSystem(EntityManager &entityManager);
			~MousePointSystem();
			void update(Context& context) override;
			System* clone() override;

			int mouseEntityID;
		};
	}
}