#pragma once

#include "memory"
#include "ECS/EntityManager.h"
#include "Context.h"

namespace ECS {
	namespace Systems {

		/// <summary>
		///	base class for all systems. 
		/// </summary>
		class System
		{
		public:
			System(EntityManager& entityManager);
			virtual ~System();
			virtual void update(Context& context) = 0;
			virtual std::unique_ptr<System> clone() = 0;

		protected:
			EntityManager *entityManager;
		};
	}	
}

