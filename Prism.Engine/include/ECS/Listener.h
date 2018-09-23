#pragma once

#include <vector>

#include "Components/Component.h"

///<summary>An interface that represents an ECS Listener</summery>
namespace ECS {
	/*class Listener
	{
	public:
		virtual void onMakeEntity(EntityHandle handle) {}
		virtual void onRemoveEntity(EntityHandle handle) {}
		virtual void onAddComponent(EntityHandle handle, unsigned int id) {}
		virtual void onRemoveComponent(EntityHandle handle, unsigned int id) {}

		const std::vector<unsigned int>& getComponentIDs() {
			return componentIDs;
		}

		inline bool shouldNotifyOnAllComponentOperations() {
			return notifyOnAllComponentOperations;
		}
		inline bool shouldNotifyOnAllEntityOperations() {
			return notifyOnAllEntityOperations;
		}

	protected:
		void setNotificationSettings(
			bool shouldNotifyOnAllComponentOperations,
			bool shouldNotifyOnAllEntityOperations) {
			notifyOnAllComponentOperations = shouldNotifyOnAllComponentOperations;
			notifyOnAllEntityOperations = shouldNotifyOnAllEntityOperations;
		}
		void addComponentID(unsigned int id) {
			componentIDs.push_back(id);
		}
	private:
		std::vector<unsigned int> componentIDs;
		bool notifyOnAllComponentOperations = false;
		bool notifyOnAllEntityOperations = false;
	};*/
}
