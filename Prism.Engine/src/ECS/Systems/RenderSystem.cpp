#include "ECS/Systems/RenderSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/AppearanceComponent.h"
#include "glm/glm.hpp"
#include <tuple>
#include "Renderer/Renderable.h"
#include "Renderer/ForwardRenderer.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"

using namespace Renderer;

namespace ECS {
	namespace Systems {

		RenderSystem::RenderSystem(std::shared_ptr<EntityManager> entityManager, int windowWidth, int windowHeight)
			: System(entityManager) {
			forwardRenderer = std::make_shared<ForwardRenderer>(windowWidth, windowHeight);
		}

		ECS::Systems::RenderSystem::~RenderSystem()
			= default;

		void RenderSystem::update(Context context)
		{
			//TODO: dit moet niet zo

			auto appearanceEntities = this->entityManager->getAllEntitiesWithComponent<AppearanceComponent>();
			vector<Renderable> rendererData;

			for (unsigned int i = 0; i < appearanceEntities.size(); i++)
			{
				auto position = this->entityManager->getComponent<PositionComponent>(appearanceEntities[i].id);
				auto appearance = appearanceEntities[i].component;

				Renderable renderable;
				renderable.model = appearanceEntities[i].component->model;

				get<0>(renderable.position) = position->x + appearance->translationX;
				get<1>(renderable.position) = appearance->translationY;
				get<2>(renderable.position) = position->y + appearance->translationZ;

				get<0>(renderable.scale) = appearance->scaleX;
				get<1>(renderable.scale) = appearance->scaleY;
				get<2>(renderable.scale) = appearance->scaleZ;


				rendererData.push_back(renderable);
			}

			forwardRenderer->draw(rendererData);
		}
	}
}