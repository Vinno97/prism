#pragma once
#include "Component.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Math/Vector3f.h"

namespace ECS
{
	namespace Components
	{
		struct AppearanceComponent : Component
		{
			std::unique_ptr<Renderer::Graphics::Models::Model> model;
			float translationX{0};
			float translationY{0};
			float translationZ{0};
			float scaleX{1};
			float scaleY{1};
			float scaleZ{1};
			float rotationX{0};
			float rotationY{0};
			float rotationZ{0};

			Math::Vector3f color{1.f, 1.f, 1.f};

			std::unique_ptr<Component> clone() override
			{
				auto appearanceComponent = std::make_unique<AppearanceComponent>();

				appearanceComponent->translationX = translationX;
				appearanceComponent->translationY = translationY;
				appearanceComponent->translationZ = translationZ;

				appearanceComponent->scaleX = scaleX;
				appearanceComponent->scaleY = scaleY;
				appearanceComponent->scaleZ = scaleZ;

				appearanceComponent->rotationX = rotationX;
				appearanceComponent->rotationY = rotationY;
				appearanceComponent->rotationZ = rotationZ;

				appearanceComponent->color = color;

				// If model is null, this would throw an exception.
				if (model)
				{
					appearanceComponent->model = std::make_unique<Renderer::Graphics::Models::Model>(*model);
				}
				return appearanceComponent;
			}
		};
	}
}
