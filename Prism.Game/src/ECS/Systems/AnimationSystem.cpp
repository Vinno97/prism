#pragma once

#include <math.h>
#include <chrono>

#include "Context.h"
#include "InputManager.h"
#include "ECS/Systems/AnimationSystem.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/ResourceSpawnComponent.h"

namespace ECS {
	namespace Systems {
		AnimationSystem::AnimationSystem(EntityManager& entityManager) : System(entityManager) {
		}

		AnimationSystem::~AnimationSystem()
			= default;

		void AnimationSystem::update(Context& context) {
			absoluteTime += context.deltaTime;
			// TODO: Misschien kan dit mooier
			for (const auto& player : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
				auto appearance = entityManager->getComponent<AppearanceComponent>(player.id);
				int rotationSpeed = 45;
				appearance->rotationY += rotationSpeed * context.deltaTime;
			}
			for (const auto& resourcePoint : entityManager->getAllEntitiesWithComponent<ResourceSpawnComponent>()) {
				auto appearance = entityManager->getComponent<AppearanceComponent>(resourcePoint.id);
				double multiplier = .1;
				auto sin = std::sin(absoluteTime) + 1;
				appearance->translationY = multiplier * sin;
			}

			for (const auto& player : entityManager->getAllEntitiesWithComponent<EnemyComponent>()) {
				auto appearance = entityManager->getComponent<AppearanceComponent>(player.id);
				double widthMultiplier = .05;
				double heightMultiplier = .1;
				// TODO: Idealiter is de schaal van een object standaard 1
				double absoluteSize = 0.002;

				auto sin = std::sin(absoluteTime / .8f) + 1;
				appearance->scaleX = absoluteSize + absoluteSize * widthMultiplier * sin;
				appearance->scaleY = absoluteSize + absoluteSize * heightMultiplier * sin;
				appearance->scaleZ = absoluteSize + absoluteSize * widthMultiplier * sin;
			}
	
		}
		System * AnimationSystem::clone()
		{
			return new AnimationSystem(*entityManager);
		}
	}
}
