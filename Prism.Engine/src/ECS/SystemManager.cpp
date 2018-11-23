#pragma once
#include "ECS/SystemManager.h"
#include <map>


namespace ECS {

	SystemManager::SystemManager()
	{
	}


	SystemManager::~SystemManager()
	{
		for (const auto systems : prioritizedSystems) {
			for (const auto type : systems.second) {
				delete type.second;
			}

		}
	}

	SystemManager::SystemManager(const SystemManager & other)
	{

		for (const auto systems : other.prioritizedSystems) {
			for (const auto type : systems.second) {
				this->prioritizedSystems[systems.first][type.first] = type.second->clone();
				type.first;
			};
		}
	}

	SystemManager & SystemManager::operator=(const SystemManager & other)
	{
		if (this != &other) {

			for (const auto systems : other.prioritizedSystems) {
				for (const auto type : systems.second) {
					this->prioritizedSystems[systems.first][type.first] = type.second->clone();
					type.first;
				};
			}
		}
		return *this;
	}

	SystemManager::SystemManager(SystemManager && other)
	{
		this->prioritizedSystems = other.prioritizedSystems;
		other.prioritizedSystems.clear();
	}

	SystemManager & SystemManager::operator=(SystemManager && other)
	{
		if (this != &other) {
			this->prioritizedSystems = other.prioritizedSystems;
			other.prioritizedSystems.clear();
		}
		return *this;
	}

	std::map<int, std::map<std::type_index, System*>>& SystemManager::getAllSystems()
	{
		return prioritizedSystems;
	}

	void SystemManager::unRegisterSystem(std::type_index systemType)
	{
		try
		{
			for (auto systems : prioritizedSystems) {
				delete systems.second.at(systemType);
				systems.second.erase(systemType);
			}

		}
		catch (const std::out_of_range&)
		{
			throw std::runtime_error(std::string("No system of type ") + systemType.name() + " found.");
		}
	}

	void SystemManager::registerSystem(std::type_index systemType, ECS::Systems::System* system)
	{
	}

	ECS::Systems::System * SystemManager::getSystem(std::type_index systemType) const
	{
		try
		{
			for (auto systems : prioritizedSystems) {
				return systems.second.at(systemType);
			}

		}
		catch (const std::out_of_range&)
		{
			throw std::runtime_error(std::string("No system of type ") + systemType.name() + " found.");
		}
	}
}