#include <math.h>
#include <chrono>

#include "Context.h"
#include "InputManager.h"
#include "ECS/Systems/AnimationSystem.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/ResourceSpawnComponent.h"
#include "ECS/Components/EnemySpawnComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/PointLightComponent.h"

namespace ECS {
	namespace Systems {
		using namespace Components;
		
		AnimationSystem::AnimationSystem(EntityManager& entityManager) : System(entityManager) {
		}

		AnimationSystem::~AnimationSystem()
			= default;

		void AnimationSystem::update(Context& context) {
			absoluteTime += context.deltaTime;
			for (const auto& player : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
				auto appearance = entityManager->getComponent<AppearanceComponent>(player.id);
				int rotationSpeed = 45;

				const float colourRed = (sin(absoluteTime/2 + 1951) / 3) + 0.5f;
				const float colourGreen = abs((sin(absoluteTime/3 + 3251) / 5) + 0.45f);
				const float colourBlue = (sin(absoluteTime/4 + 13337) / 7) + 0.4f;

				appearance->rotationY += rotationSpeed * context.deltaTime;
				appearance->color = Math::Vector3f(colourRed, colourGreen, colourBlue);
				auto pointLight = entityManager->getComponent<PointLightComponent>(player.id);
				pointLight->color = Math::Vector3f(appearance->color.x + 0.5, appearance->color.y + 0.5, appearance->color.z + 0.5);
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
				double absoluteSize = 0.002;

				auto sin = std::sin(absoluteTime / .8f) + 1;
				appearance->scaleX = absoluteSize + absoluteSize * widthMultiplier * sin;
				appearance->scaleY = absoluteSize + absoluteSize * heightMultiplier * sin;
				appearance->scaleZ = absoluteSize + absoluteSize * widthMultiplier * sin;
			}
			for (const auto& spawnPoint : entityManager->getAllEntitiesWithComponent<EnemySpawnComponent>()) {
				auto appearance = entityManager->getComponent<AppearanceComponent>(spawnPoint.id);
				auto position = entityManager->getComponent<PositionComponent>(spawnPoint.id);
				double widthMultiplier = .15;
				double heightMultiplier = .1;
				double absoluteSize = 0.002;

				auto sin = std::sin(absoluteTime);

				auto x = sin / (1 - (-1));
				auto result = 0 + (360 - 0) * x;

				appearance->rotationY= result;
			}
		}
	}
}
