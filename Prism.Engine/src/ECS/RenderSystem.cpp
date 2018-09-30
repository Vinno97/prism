#include "ECS/RenderSystem.h"

namespace ECS {
	
	RenderSystem::RenderSystem(const EntityManager* entityManager) 
		: System(entityManager)
	{
	}
	RenderSystem::~RenderSystem()
	{
	}
	void RenderSystem::Update(Context deltaTime)
	{
	}
}