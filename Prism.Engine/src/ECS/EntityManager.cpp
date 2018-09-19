#include "ECS/EntityManager.h"

namespace ECS {
	EntityManager::EntityManager()
	{
	}


	EntityManager::~EntityManager()
	{
	}

	/*void EntityManager::addComponentInternal(EntityHandle handle, std::vector<std::pair<unsigned int, unsigned int> >& entity, unsigned int componentID, Component* component)
	{

		createfn = BaseECSComponent::getTypeCreateFunction(componentID);
		std::pair<unsigned int, unsigned int> newPair;
		newPair.first = componentID;
		newPair.second = createfn(components[componentID], handle, component);
		entity.push_back(newPair);
	}*/

}