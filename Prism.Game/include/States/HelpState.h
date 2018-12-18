#pragma once

#include <memory>
#include "State.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

namespace States {
	class HelpState : public State
	{
	public:
		HelpState();

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onEnter(Context & context) override;
		void onLeave(Context & context) override;

		template<typename T, typename = std::enable_if_t < std::is_base_of<State, T>::type::value>>
		void setPreviousState(Context &context) {
			previousState = context.stateMachine->getState<HelpState>();
		}

		~HelpState();

	private:
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;
		State * previousState;
	};
}