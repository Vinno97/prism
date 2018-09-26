#pragma once
#include "ECS/EntityManager.h"
#include "Context.h"
namespace ECS {
	class System
	{
	public:
		System(const EntityManager*);
		System(int ID);
		~System();
		virtual void Update(Context context)=0;
	};
}

