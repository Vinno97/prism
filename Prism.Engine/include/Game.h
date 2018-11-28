#pragma once

#include "State.h"
#include "Context.h"

class Game : public State
{

public:
	Game();
	~Game();

	virtual void onInit(Context &context) override;
	virtual void onUpdate(Context &context) override;
	virtual void onEnter(Context &context) override;
	virtual void onLeave() override;

private:
	Context context;
};
