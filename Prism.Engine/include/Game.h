#pragma once

#include "State.h"
#include "Context.h"

class Game : State
{


public:
	Game();
	~Game();

	void onEnter() override;
	void onLeave() override;

private:
	Context context;

};


