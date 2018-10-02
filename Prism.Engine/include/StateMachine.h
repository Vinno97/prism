#pragma once
#include "State.h"
#include <map>
#include <list>
#include <typeindex>

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	template<class T, typename = std::enable_if < std::is_base_of<State, T>::value>>
	void setState()
	{
		State &T = existingStates[type];

		this->currentState->onLeave();
		this->currentState = getState(state);
		this->currentState->onEnter();
	}

	template<class T>
	void addState(T& state) {
		const std::type_index type = std::type_index(typeid(state));
		if (existingStates.find(type) != existingStates.end()) {
			std::map<unsigned int, State*> *states = &existingStates.at(type);
		}
		existingStates[type] = new T(state);
	}

	template<typename T, typename = std::enable_if < std::is_base_of<State, T>::value>>
	T* getState(T& state) const {
		auto it = existingStates.begin();
		// Iterate through the map
		while (it != existingStates.end())
		{
			// Check if value of this entry matches with given value
			if (it->second == state)
			{
				return &it->second;
			}
			// Go to next entry in map
			it++;
		}
	}

	State *getCurrentState();

private:
	State *currentState;

	// keeps a list of States
	std::map<std::type_index, State*> existingStates;

};


