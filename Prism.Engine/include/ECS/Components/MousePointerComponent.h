#pragma once

#include "ECS/Components/Component.h"

struct MousePointerComponent : ECS::Components::Component{
	Component* Clone() override {
		MousePointerComponent* component = new MousePointerComponent();
		return component;
	}
};