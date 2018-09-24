#pragma once
#include "State.h"

class GameState:State
{
public:
	GameState();
	~GameState();

	void update(Context context) override;
	void onEnter() override;
	void onLeave() override;
};

