#pragma once

#include "State.h"
#include "ECS/Systems/KeyboardInputSystem.h"
class PauseState : public State
{
public:
	PauseState();

	void onInit(Context &context) override;
	void onUpdate(Context &context) override;
	void onEnter() override;
	void onLeave() override;
	~PauseState();

private:
	bool isPressable = false;
};

