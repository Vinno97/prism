#include "StateMachine.h"
#include <string>
#include <algorithm>

StateMachine::StateMachine()
= default;

State* StateMachine::getCurrentState() const
{
	return this->currentState;
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

bool StateMachine::hasState(const State& state) const {
	for (const auto& s : existingStates) {
		if (s.second.get() == &state) {
			return true;
		}
	}
	return false;
}

std::vector<State*> StateMachine::getAllStates() const {
	std::vector<State*> states{};
	std::transform(existingStates.begin(), existingStates.end(), std::back_inserter(states), [](auto& pair) { return pair.second.get(); });
	return states;
}

void StateMachine::destroyEolStates(Context& context) {
    for (const auto& state : eolQueue) {
		state->destroy(context);
    }
    eolQueue.clear();
}