#include "ECS/Systems/RenderSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/SceneComponent.h"
#include "glm/glm.hpp"
#include <tuple>
#include "Renderer/Renderable.h"
#include "Renderer/ForwardRenderer.h"
#include "Renderer/Scene.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"

using namespace Renderer;

namespace ECS {
	namespace Systems {

		RenderSystem::RenderSystem(EntityManager &entityManager, int windowWidth, int windowHeight)
			: System(entityManager) {
			forwardRenderer = std::make_shared<ForwardRenderer>(windowWidth, windowHeight);
			camera.move(0, 3.f, 4.f);
			camera.rotate(-25.f, 0.f, 0.f);
		}

		ECS::Systems::RenderSystem::~RenderSystem()
			= default;

		void RenderSystem::update(Context& context)
		{
			auto appearanceEntities = this->entityManager->getAllEntitiesWithComponent<AppearanceComponent>();
			vector<Renderable> rendererData;
			auto sceneEntity = this->entityManager->getAllEntitiesWithComponent<SceneComponent>()[0].component;

			auto players = entityManager->getAllEntitiesWithComponent<PlayerComponent>();
			if (!players.empty()) {
				auto playerPosition = entityManager->getComponent<PositionComponent>(players.front().id);
				camera.position.x -= (camera.position.x - playerPosition->x) * context.deltaTime * 2;
				camera.position.z -= (camera.position.z - 4.f - playerPosition->y) * context.deltaTime * 2;
			}			

			for (unsigned int i = 0; i < appearanceEntities.size(); i++)
			{
				auto position = this->entityManager->getComponent<PositionComponent>(appearanceEntities[i].id);
				AppearanceComponent* appearance = appearanceEntities[i].component;

				Renderable renderable;
				renderable.model = appearance->model.get();

				get<0>(renderable.position) = position->x + appearance->translationX;
				get<1>(renderable.position) = appearance->translationY;
				get<2>(renderable.position) = position->y + appearance->translationZ;

				get<0>(renderable.scale) = appearance->scaleX;
				get<1>(renderable.scale) = appearance->scaleY;
				get<2>(renderable.scale) = appearance->scaleZ;

				get<0>(renderable.rotation) = appearance->rotationX;
				get<1>(renderable.rotation) = appearance->rotationY;
				get<2>(renderable.rotation) = appearance->rotationZ;

				renderable.color = appearance->color;

				rendererData.push_back(renderable);
			}

			forwardRenderer->draw(camera, rendererData, sceneEntity->scene);
		}

		System * RenderSystem::clone()
		{
			RenderSystem* system = new RenderSystem(*entityManager, forwardRenderer->width, forwardRenderer->height);
			return system;
		}
	}
}
