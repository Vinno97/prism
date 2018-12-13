#pragma once

#include <cstdio>
#include <iostream>


#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS
{
	namespace Systems
	{
		System::System(EntityManager& entityManager_) : entityManager(&entityManager_)
		{
		};

		System::~System()
		= default;
	}
}
