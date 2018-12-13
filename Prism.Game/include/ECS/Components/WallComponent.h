#pragma once

#include "ECS/Components/Component.h"

namespace ECS
{
	namespace Components
	{
		struct WallComponent : Component
		{
			std::unique_ptr<Component> clone() override
			{
				return std::make_unique<WallComponent>();
			}
		};
	}
}
