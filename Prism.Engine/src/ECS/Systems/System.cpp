#pragma once

#include <cstdio>
#include <iostream>  


#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		System::System(EntityManager &entityManager) {
			this->entityManager = entityManager;
		}

		System::~System()
		= default;
	}
}