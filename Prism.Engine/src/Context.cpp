#include "Context.h"

Context::Context()
= default;

const double Context::getDeltatime() { return deltaTime; }
Window *Context::getWindow() { return window; }
StateMachine *Context::getStateMachine() { return stateMachine; }
void Context::setDeltatime(int newDeltaTime) { this->deltaTime = newDeltaTime; }
void Context::setWindow(Window *newWindow) { this->window = newWindow; }
void Context::setStateMachine(StateMachine *newStateMachine) { this->stateMachine = newStateMachine; }

Context::~Context()
= default;
