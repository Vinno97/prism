#pragma once

#include "ECS/EntityManager.h"
#include "Context.h"
#include "ECS/EntityManager.h"

namespace ECS {
	namespace Systems {

		/// <summary>
		///	base class for all systems. 
		/// </summary>
		class System
		{
		public:
			System(std::shared_ptr<EntityManager> entityManager);
			virtual ~System();
			virtual void update(Context context) = 0;

		protected:
			std::shared_ptr<EntityManager> entityManager;
		};
	}	
}

