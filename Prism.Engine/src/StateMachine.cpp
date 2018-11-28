#include "StateMachine.h"
#include <string>

StateMachine::StateMachine()
= default;

StateMachine::~StateMachine() {
}

State* StateMachine::getCurrentState() const
{
	return this->currentState;
}

void StateMachine::setState(std::type_index type) {
	if (this->currentState != nullptr)
		this->currentState->onLeave();

	this->currentState = getState(type);
	this->currentState->onEnter();
}

State* StateMachine::getState(std::type_index type) const {
	try
	{
		return existingStates.at(type).get();
	}
	catch (const std::runtime_error&)
	{
		throw std::runtime_error("There can only one type of " + *type.name() + *" registered");
	}
}

bool StateMachine::hasState(std::type_index type) const {
	return existingStates.find(type) != existingStates.end();
}