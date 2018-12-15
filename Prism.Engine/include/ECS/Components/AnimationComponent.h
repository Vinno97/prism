#pragma once

#include "Component.h"
#include "Renderer/Animation.h"
#include <map>
#include <tuple>
#include <functional>

namespace ECS
{
	namespace Components
	{

		struct AnimationComponent : Component
		{
			AnimationComponent() = default;

			//Base is 0 (no animation)
			//Max is always 100
			//To start animation add new animation to map and set float value anywhere from 0 to 100
			//Animation will automatically be removed when finished
			//The boolean indicates whether the entity should be removed when the animation is finished
			std::map<Renderer::Animation, std::tuple<float, bool>> currentAnimations;

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
