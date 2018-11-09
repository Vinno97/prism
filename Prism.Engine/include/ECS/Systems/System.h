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
			System(EntityManager& entityManager);
			virtual ~System();
			virtual void update(Context context) = 0;
			virtual System* clone() = 0;

			System(const System &system) = delete;
			System(const System &&system) = delete;
			System &operator=(const System &system) = delete;
			System &operator=(System &&system) = delete;
		protected:
			EntityManager *entityManager;
		};
	}	
}

