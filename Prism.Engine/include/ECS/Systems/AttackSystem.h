#pragma once
#include "ECS/Systems/System.h"
#include "Renderer/ForwardRenderer.h"
#include "Physics/AABBCollider.h"
#include "Physics/BoundingBox.h"

using namespace Renderer;
namespace ECS {
	namespace Systems {
		class AttackSystem : public System
		{
		public:
			AttackSystem(std::shared_ptr<EntityManager> entityManager);
			~AttackSystem();

			void update(Context context) override;

		private:
			AABBCollider aabbCollider;
		};
	
	}
}