#pragma once

#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class AttackSystem : public System
		{
		public:
			AttackSystem(EntityManager* entityManager);
			~AttackSystem();

			void Attack(int damage);
		};
	}
}