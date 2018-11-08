#pragma once

#include "ECS/Systems/System.h"
#include "Renderer/ForwardRenderer.h"

//using namespace Renderer;
namespace ECS {
	namespace Systems {
		class RenderSystem : public System
		{
		public:
			RenderSystem(EntityManager &entityManager, int windowWidth, int windowHeight);
			~RenderSystem();
			void update(Context context) override;
			System* clone() override;
		private:
			std::shared_ptr<Renderer::ForwardRenderer> forwardRenderer;
			Renderer::Camera camera;
		};


	}
}