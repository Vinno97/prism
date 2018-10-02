#pragma once
#include "State.h"

class MenuState : State
{
public:
	MenuState();
	~MenuState();

	void update(Context context) override;
	void onEnter() override;
	void onLeave() override;

private:
	Context context;
};

