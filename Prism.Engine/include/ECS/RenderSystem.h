#pragma once

#include "ECS/System.h"

namespace ECS {
	class RenderSystem : public System
	{
	public:
		RenderSystem(const EntityManager* entityManager);
		~RenderSystem();
		void Update(Context context) override;
	private:

	};
}