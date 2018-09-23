#pragma once

#include "Context.h"
#include "ECS/EntityManager.h"

namespace ECS {
	namespace Systems {
		class System
		{
		public:
			System(EntityManager* entityManager);
			~System();
			void virtual update(Context c);
		protected:
			EntityManager* entityManager;
		};
	}
}