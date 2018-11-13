#include "States/PauseState.h"
#include "StateMachine.h";
#include "States/PrismGame.h"; 

namespace States {
	PauseState::PauseState()
	{
	}

	void PauseState::onInit(Context & context)
	{
	}

	void PauseState::onUpdate(Context & context)
	{

		auto input = context.inputManager;
		if (input->isKeyPressed(Key::KEY_ESCAPE) && canPressEscape) {
			canPressEscape = false;
			context.stateMachine->setState<PrismGame>();
		}

		if (!input->isKeyPressed(Key::KEY_ESCAPE)) {
			canPressEscape = true;
		}


	}

	void PauseState::onEnter()
	{
	}


	void PauseState::onLeave()
	{
	}

	PauseState::~PauseState()
	{
	}
}