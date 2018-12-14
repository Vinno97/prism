#pragma once

#include "Component.h"
#include "Renderer/Animation.h"
#include <map>

namespace ECS
{
	namespace Components
	{

		struct AnimationComponent : Component
		{
			AnimationComponent() = default;

			std::map<Renderer::Animation, int> currentAnimations;

			std::unique_ptr<Component> clone() override
			{
				auto component = std::make_unique<AnimationComponent>();

				for (auto& currentAnimation : currentAnimations)
				{
					component->currentAnimations[currentAnimation.first] = currentAnimation.second;
				}

				return component;
			}
		};
	}
}
