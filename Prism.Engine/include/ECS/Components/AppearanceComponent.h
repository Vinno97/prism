#pragma once
#include "Component.h"
#include "Renderer/Graphics/Models/Model.h"

namespace ECS {
	namespace Components {
		struct AppearanceComponent : Component {
			std::unique_ptr<Renderer::Graphics::Models::Model> model;
			float translationX = 0;
			float translationY = 0;
			float translationZ = 0;
			float scaleX = 1;
			float scaleY = 1;
			float scaleZ = 1;
			float rotationX = 0;
			float rotationY = 0;
			float rotationZ = 0;

			Component* Clone() 
			{
				AppearanceComponent* appearanceComponent = new AppearanceComponent();
	
				appearanceComponent->translationX = translationX;
				appearanceComponent->translationY = translationY;
				appearanceComponent->translationZ = translationZ;
	
				appearanceComponent->scaleX = scaleX;
				appearanceComponent->scaleY = scaleY;
				appearanceComponent->scaleZ = scaleZ;
	
				appearanceComponent->rotationX = rotationX;
				appearanceComponent->rotationY = rotationY;
				appearanceComponent->rotationZ = rotationZ;
	
				appearanceComponent->model = std::make_unique<Renderer::Graphics::Models::Model>(*model);
	
				return appearanceComponent;
			}
		};
	}
}