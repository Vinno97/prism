#pragma once

#include "ECS/Systems/System.h"
#include "Renderer/ForwardRenderer.h"
#include "Math/Vector3.h"

namespace ECS {
	namespace Systems {
		class RenderSystem : public System
		{
		public:
			RenderSystem(EntityManager &entityManager, int windowWidth, int windowHeight);
			~RenderSystem();
			void update(Context& context) override;
		private:
			std::shared_ptr<Renderer::ForwardRenderer> forwardRenderer;
			Math::Vector3f pos{ -45.f, 3.5f, -15 };
		};


	}
}
