#pragma once

#include <cstdio>
#include <iostream>  


#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		System::System(EntityManager* entityManager) {
			this->entityManager = entityManager;
		}

		System::~System()
			= default;

		void System::update(Context c)
		{
			std::cerr << "Error. Update function of base System is not overridden";
		}



	}
}