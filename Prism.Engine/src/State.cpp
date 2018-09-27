#include "State.h"

State::State()
= default;

State::~State()
= default;

void State::update(Context context)
{
	this->context = context;
}

void State::onEnter()
{
}

void State::onLeave()
{
}

