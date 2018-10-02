#include "StateMachine.h"
#include <string>

StateMachine::StateMachine()
= default;

StateMachine::~StateMachine()
= default;

State* StateMachine::getCurrentState()
{
	return this->currentState;
}
