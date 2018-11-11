#pragma once
#include "ECS/SystemManager.h"
#include <map>


namespace ECS {

	SystemManager::SystemManager()
	{
	}


	SystemManager::~SystemManager()
	{
		for (const auto type : systems) {
			delete type.second;
		}
	}

	SystemManager::SystemManager(const SystemManager & other)
	{
		for (const auto type : other.systems) {
			this->systems[type.first] = type.second->clone();
			type.first;
		};

		
		//this->systems.insert(other.systems.begin(), other.systems.end());
	}

	SystemManager & SystemManager::operator=(const SystemManager & other)
	{
		if (this != &other) {
			for (const auto type : other.systems) {
				this->systems[type.first] = type.second->clone();
				type.first;
			};
		}
		return *this;
	}

	SystemManager::SystemManager(SystemManager && other)
	{
		this->systems = other.systems;
		other.systems.clear();
	}

	SystemManager & SystemManager::operator=(SystemManager && other)
	{
		if (this != &other) {
			this->systems = other.systems;
			other.systems.clear();
		}
		return *this;
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

	void SystemManager::registerSystem(std::type_index systemType, ECS::Systems::System* system)
	{
	}

	ECS::Systems::System * SystemManager::getSystem(std::type_index systemType) const
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