#include "State.h"
#include "Context.h"


State::State()
= default;


State::~State()
= default;

void State::update(Context newContext)
{
	this->context = newContext;
}

void State::onEnter()
{
}

void State::onLeave()
{
}
