#include "ECS/Systems/RenderSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/AppearanceComponent.h"
#include "glm/glm.hpp"
#include <tuple>


namespace ECS {
	namespace Systems {
		RenderSystem::RenderSystem(EntityManager * entityManager)
			: System(entityManager)
		{

		}

		ECS::Systems::RenderSystem::~RenderSystem()
			= default;

		void RenderSystem::update(Context context)
		{
			auto appearanceEntities = this->entityManager->getAllEntitiesWithComponent<AppearanceComponent>();
			vector<std::tuple <Model*, float, float, float>> rendererData;

			for (unsigned int i = 0; i < appearanceEntities.end; i++)
			{
				auto position = this->entityManager->getComponent<PositionComponent>(appearanceEntities[i].id);
				auto appearance = appearanceEntities[i];
				auto model = appearanceEntities[i].component->model;

				auto x = position->x + appearance.component->x;
				auto y = position->y + appearance.component->y;
				auto z = appearance.component->z;


				std:tuple<Model*, float, float, float> temp12(model, position->x, position->y, 0);
				rendererData.push_back(temp12);

			}
			//TODO: stuur het model naar de forward renderer

		}
	}
}