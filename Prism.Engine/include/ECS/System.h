#pragma once
#include "ECS/EntityManager.h"
#include "Context.h"
namespace ECS {

	/// <summary>
	///	base class for all systems. 
	/// </summary>

	class System
	{
	public:
		System(const EntityManager*);
		~System();
		virtual void Update(Context context)=0;
	};
}

