#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "EntityFactory.h"
#include "Enums/ResourceTypeEnum.h"

namespace ECS
{
	namespace Systems
	{
		using namespace Components;

		class ResourceGatherSystem : public System
		{
		public:
			explicit ResourceGatherSystem(EntityManager& entityManager) : System(entityManager)
			{
			};
			void update(Context& context) override;
		private:

			EntityFactory entityFactory;
			/// <summary>
			/// Checks if an entity with the resourceGatherComponent is in range to collect the resource
			/// </summay>
			void spawnResourceBlob(Math::Vector2<double>, unsigned targetId, Enums::ResourceType resourceType,
			                       float value);
		};
	}
}
