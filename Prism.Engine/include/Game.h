#pragma once

#include "State.h"
#include "Context.h"

class Game : public State
{
public:
	Game();
	~Game();

	void onInit(Context& context) override;
	void onUpdate(Context& context) override;
	void onEnter(Context& context) override;
	void onLeave(Context& context) override;

private:
	Context context;
};
