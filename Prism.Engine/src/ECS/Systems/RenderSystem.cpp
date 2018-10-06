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

		ForwardRenderer forwardRenderer = ForwardRenderer(1920,1080);
		RenderSystem::RenderSystem(EntityManager * entityManager)
			: System(entityManager)
		{

		}

		ECS::Systems::RenderSystem::~RenderSystem()
			= default;

		void RenderSystem::update(Context context)
		{
			auto appearanceEntities = this->entityManager->getAllEntitiesWithComponent<AppearanceComponent>();
			vector<Renderable> rendererData;

			for (unsigned int i = 0; i < appearanceEntities.size(); i++)
			{
				auto position = this->entityManager->getComponent<PositionComponent>(appearanceEntities[i].id);
				auto appearance = appearanceEntities[i];
				auto model = appearanceEntities[i].component->model;


				Renderable renderable;
				get<0>(renderable.position) = position->x + appearance.component->x;
				get<1>(renderable.position) = position->y + appearance.component->y;
				get<2>(renderable.position) = appearance.component->z;

				rendererData.push_back(renderable);

			}
			
			forwardRenderer.draw(rendererData);
		}
	}
}