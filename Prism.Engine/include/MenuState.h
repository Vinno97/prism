#pragma once
#include "State.h"

class MenuState : public State
{
public:
	MenuState();
	~MenuState();

	void onUpdate(Context &context) override;
	void onEnter(Context & context) override;
	void onLeave(Context & context) override;
};

