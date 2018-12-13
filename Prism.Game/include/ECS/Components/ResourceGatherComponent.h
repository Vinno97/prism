#pragma once

#include "ECS/Components/Component.h"

namespace ECS
{
	namespace Components
	{
		struct ResourceGatherComponent : Component
		{
			ResourceGatherComponent() = default;

			ResourceGatherComponent(float range_) : gatherRange(range_)
			{
			};

			const float gatherRange = 1;

			std::unique_ptr<Component> clone() override
			{
				return std::make_unique<ResourceGatherComponent>();
			}
		};
	}
}
