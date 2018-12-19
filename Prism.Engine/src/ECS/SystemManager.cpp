#include "ECS/SystemManager.h"
#include <map>


namespace ECS {

	SystemManager::SystemManager()
	{
	}


	SystemManager::~SystemManager()
	{
		
	}

	std::map<int, std::map<std::type_index, std::unique_ptr<System>>>& SystemManager::getAllSystems()
	{
		return prioritizedSystems;
	}

	void SystemManager::unRegisterSystem(std::type_index systemType)
	{
		try
		{
			for (auto& systems : prioritizedSystems) {
				systems.second.erase(systemType);
			}

		}
		catch (const std::out_of_range&)
		{
			throw std::runtime_error(std::string("No system of type ") + systemType.name() + " found.");
		}
	}


	System* SystemManager::getSystem(std::type_index systemType) const
	{
		try
		{
			for (auto& systems : prioritizedSystems) {
				return systems.second.at(systemType).get();
			}

		}
		catch (const std::out_of_range&)
		{
			throw std::runtime_error(std::string("No system of type ") + systemType.name() + " found.");
		}
	}
}