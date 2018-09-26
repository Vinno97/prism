#include "ECS/RenderSystem.h"

namespace ECS {
	int systemID;
	RenderSystem::RenderSystem(const EntityManager* entityManager) 
		: System(entityManager)
	{
	}
	RenderSystem::~RenderSystem()
	{
	}
	RenderSystem::RenderSystem(int id)
		: System(id)
	{
		systemID = id;
	}

	void RenderSystem::Update(Context deltaTime)
	{
	}
}