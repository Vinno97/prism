#include "ECS/Systems/RenderSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/SceneComponent.h"
#include "ECS/Components/CameraComponent.h"
#include "ECS/Components/PointLightComponent.h"
#include "glm/glm.hpp"
#include <tuple>
#include "Renderer/Renderable.h"
#include "Renderer/ForwardRenderer.h"
#include "Renderer/Scene.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "ECS/Components/PositionComponent.h"

using namespace Renderer;
using namespace ECS;
using namespace Systems;
using namespace Components;
using namespace std;

namespace ECS {
	namespace Systems {
		using namespace Components;

		RenderSystem::RenderSystem(EntityManager &entityManager, int windowWidth, int windowHeight)
			: System(entityManager) {
			forwardRenderer = std::make_shared<ForwardRenderer>(windowWidth, windowHeight);
			auto cameraComponent = this->entityManager->getAllEntitiesWithComponent<CameraComponent>()[0].component;
			auto camera = &cameraComponent->camera;

		}

		ECS::Systems::RenderSystem::~RenderSystem()
			= default;

		void RenderSystem::update(Context& context)
		{
			auto appearanceEntities = this->entityManager->getAllEntitiesWithComponent<AppearanceComponent>();
			vector<Renderable> rendererData;
			auto sceneComponent = this->entityManager->getAllEntitiesWithComponent<SceneComponent>()[0].component;
			auto cameraComponent = this->entityManager->getAllEntitiesWithComponent<CameraComponent>()[0].component;
			auto camera = &cameraComponent->camera;

			auto players = entityManager->getAllEntitiesWithComponent<PlayerComponent>();
			if (!players.empty()) {
				auto playerPosition = entityManager->getComponent<PositionComponent>(players.front().id);
				camera->position.x -= (camera->position.x - playerPosition->x) * context.deltaTime * 2;
				camera->position.z -= (camera->position.z - 4.f - playerPosition->y) * context.deltaTime * 2;
			}


			for (unsigned int i = 0; i < appearanceEntities.size(); i++)
			{
				auto position = this->entityManager->getComponent<PositionComponent>(appearanceEntities[i].id);
				AppearanceComponent* appearance = appearanceEntities[i].component;

				Renderable renderable;
				renderable.model = appearance->model.get();

				std::get<0>(renderable.position) = position->x + appearance->translationX;
				std::get<1>(renderable.position) = appearance->translationY;
				std::get<2>(renderable.position) = position->y + appearance->translationZ;

				std::get<0>(renderable.scale) = appearance->scaleX;
				std::get<1>(renderable.scale) = appearance->scaleY;
				std::get<2>(renderable.scale) = appearance->scaleZ;

				std::get<0>(renderable.rotation) = appearance->rotationX;
				std::get<1>(renderable.rotation) = appearance->rotationY;
				std::get<2>(renderable.rotation) = appearance->rotationZ;

				renderable.color = appearance->color;

				rendererData.push_back(renderable);
			}
			std::vector<Renderer::PointLight> lights;
			auto lightEntities = entityManager->getAllEntitiesWithComponent<PointLightComponent>();
			for (unsigned int i = 0; i < lightEntities.size(); i++) {
				auto position = this->entityManager->getComponent<PositionComponent>(lightEntities[i].id);
				Renderer::PointLight pl{ Math::Vector3f{float(position->x), 1, float(position->y)}, lightEntities[i].component->color };
				lights.push_back(pl);
			}

			auto& input = context.inputManager;

			//if (input->isKeyPressed(Key::KEY_I)) {
			if (input->isKeyPressed(Key::KEY_H)) {
				forwardRenderer->loadPipelines();
			}

			forwardRenderer->draw(cameraComponent->camera, rendererData, sceneComponent->scene, lights, pos);
		}
	}
}
