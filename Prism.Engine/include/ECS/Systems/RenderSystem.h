#pragma once

#include "ECS/Systems/System.h"
#include "Renderer/ForwardRenderer.h"

using namespace Renderer;
namespace ECS {
	namespace Systems {
		class RenderSystem : public System
		{
		public:
			RenderSystem(std::shared_ptr<EntityManager> entityManager, int windowWidth, int windowHeight);
			~RenderSystem();
			void update(Context context) override;
		private:
			std::shared_ptr<ForwardRenderer> forwardRenderer;
			Camera camera;
		};


	}
}