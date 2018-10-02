#pragma once

#include "Context.h"

class Game
{
public:
	Game();
	~Game();

	virtual void update(Context context);
};
