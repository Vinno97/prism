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
				//Place incrementation for iterator inside for loop so we can delete whilst iterating
				for (auto it = animationComponent->currentAnimations.cbegin(); it != animationComponent->currentAnimations.cend(); )
				{
					Renderer::Animation key = it->first;
			
					if (std::get<0>(animationComponent->currentAnimations[key]) > 0) {
						std::get<0>(animationComponent->currentAnimations[key]) -= 10.f;
						++it;
					} else
					{
						if(std::get<1>(animationComponent->currentAnimations[key]))
						{
							entityManager->removeEntity(target.id);
							break;
						}
						animationComponent->currentAnimations.erase(it++);
					}
				}
			}
		}
	}
}
