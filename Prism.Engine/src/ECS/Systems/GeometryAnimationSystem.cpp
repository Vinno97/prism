#include "Renderer/Animation.h"
#include "Context.h"
#include "ECS/Systems/GeometryAnimationSystem.h"
#include "ECS/Components/AnimationComponent.h"

namespace ECS {
	using namespace Components;
	namespace Systems {
		GeometryAnimationSystem::GeometryAnimationSystem(EntityManager& entityManager) : System(entityManager) {

		}

		void GeometryAnimationSystem::update(Context& context) {
			auto targets = entityManager->getAllEntitiesWithComponent<AnimationComponent>();
			for (auto target : targets)
			{
				auto animationComponent = target.component;
				for (auto it = animationComponent->currentAnimations.begin(); it != animationComponent->currentAnimations.end(); ++it)
				{
					Renderer::Animation key = it->first;

					if (animationComponent->currentAnimations[key] > 0) {
						animationComponent->currentAnimations[key] -= context.deltaTime/100;
					}
				}
			}
		}
	}
}
