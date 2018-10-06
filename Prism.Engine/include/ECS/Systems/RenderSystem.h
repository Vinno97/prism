#pragma once

#include "ECS/Systems/System.h"
#include "Renderer/ForwardRenderer.h"

using namespace Renderer;
namespace ECS {
	namespace Systems {
		class RenderSystem : public System
		{
		public:
			RenderSystem(EntityManager* entityManager);
			~RenderSystem();
			void update(Context context) override;
		private:
			
		};


	}
}