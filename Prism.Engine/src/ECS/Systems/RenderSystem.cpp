#include "ECS/Systems/RenderSystem.h"
#include "ECS/EntityManager.h"

namespace ECS {
	namespace Systems {
		RenderSystem::RenderSystem(std::shared_ptr<EntityManager> entityManager)
			: System(entityManager) {}

		ECS::Systems::RenderSystem::~RenderSystem()
			= default;

		void RenderSystem::update(Context context)
		{
		}
	}
}