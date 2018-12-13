#pragma once

#include "Component.h"

namespace ECS
{
	namespace Components
	{
		struct PlayerComponent : Component
		{
			std::unique_ptr<Component> clone() override
			{
				return std::make_unique<PlayerComponent>();
			}
		};
	}
}
