#include "StateMachine.h"


StateMachine::StateMachine()
= default;

StateMachine::~StateMachine()
= default;

State *StateMachine::getState() {
	return currentState;
}

void StateMachine::setState(State *newState) {
	this->currentState = newState;
}