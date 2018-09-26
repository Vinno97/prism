#include "StateMachine.h"


StateMachine::StateMachine() {
	currentState;
}

StateMachine::~StateMachine()
= default;

State StateMachine::getState() {
	return currentState;
}

void StateMachine::setState(State newState) {
	StateMachine::currentState = newState;
}