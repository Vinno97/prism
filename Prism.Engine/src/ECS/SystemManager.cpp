#pragma once
#include "ECS/SystemManager.h"
#include <map>


namespace ECS {

	SystemManager::SystemManager()
	{
	}


	SystemManager::~SystemManager()
	{
	}
	void SystemManager::unRegisterSystem(std::type_index systemType)
	{
		try
		{
			delete systems.at(systemType);
			systems.erase(systemType);
		}
		catch (const std::out_of_range&)
		{
			throw std::runtime_error(std::string("No system of type ") + systemType.name() + " found.");
		}
	}
	void SystemManager::registerSystem(std::type_index systemType, System* system)
	{
	}
	System * SystemManager::getSystem(std::type_index systemType) const
	{
		try
		{
			return systems.at(systemType);
		}
		catch (const std::out_of_range&)
		{
			throw std::runtime_error(std::string("No system of type ") + systemType.name() + " found.");
		}
	}
}