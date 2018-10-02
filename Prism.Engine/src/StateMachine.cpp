#include "StateMachine.h"
#include <string>

StateMachine::StateMachine()
= default;

StateMachine::~StateMachine()
= default;



State* StateMachine::getState(unsigned int stateId, std::type_index stateType) const
{
	try {
		return existingStates.at(stateType).at(stateId);
	}
	catch (const std::out_of_range&) {
		throw std::runtime_error(std::string("No component of type ") + stateType.name() + " found for state " + std::to_string(stateId));
	}
}
