#pragma once

#include "State.h"
#include "Context.h"

class Game : State
{


public:
	Game();
	~Game();

	virtual void update(Context context) override;
	virtual void onEnter() override;
	virtual void onLeave() override;

private:
	Context context;

};


