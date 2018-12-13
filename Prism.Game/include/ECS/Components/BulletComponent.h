#pragma once

#include "ECS/Components/Component.h"

namespace ECS
{
	namespace Components
	{
		struct BulletComponent : Component
		{
			float lifeTime;

			std::unique_ptr<Component> clone() override
			{
				return std::make_unique<BulletComponent>();
			}
		};
	}
}
