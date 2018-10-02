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
	void setState(T& state)
	{
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
	T* getState(T& stateId) const {
		const std::type_index type{ std::type_index(typeid(T)) };
		return static_cast<T*>(getState(stateId, type));

	}

private:
	State *currentState;
	State* getState(unsigned int stateId, std::type_index stateType) const;

	// keeps a list of States
	std::map<std::type_index, std::map<unsigned int, State*>> existingStates;

};


