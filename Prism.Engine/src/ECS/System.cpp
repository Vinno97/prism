#include "ECS/System.h"
#include "ECS/EntityManager.h"
#include "Context.h"


namespace ECS {
	int id;
	const EntityManager* entityManager;
	System::System(const EntityManager* entityManager)
	{
		ECS::entityManager = entityManager;
	}


	System::~System()
	{
	}
}