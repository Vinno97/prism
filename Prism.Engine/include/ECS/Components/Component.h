#pragma once
#include <memory>

namespace ECS
{
	namespace Components
	{
		struct Component
		{
			Component() = default;
			virtual ~Component() = default;
			virtual std::unique_ptr<Component> clone() = 0;
		};
	}
}
