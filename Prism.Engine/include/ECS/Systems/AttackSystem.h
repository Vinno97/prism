#pragma once
#include "ECS/Systems/System.h"
#include "Renderer/ForwardRenderer.h"

using namespace Renderer;
namespace ECS {
	namespace Systems {
		class AttackSystem : public System
		{
		public:
			AttackSystem(std::shared_ptr<EntityManager> entityManager);
			~AttackSystem();

			void Attack(Context context);
		};
	
	}
}