#pragma once

#include "ECS/Components/Component.h"

struct MousePointerComponent : ECS::Components::Component
{
	std::unique_ptr<Component> clone() override
	{
		return std::make_unique<MousePointerComponent>();
	}
};
