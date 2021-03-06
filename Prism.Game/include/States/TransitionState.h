#pragma once

#include <memory>
#include "State.h"
#include "StateMachine.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

namespace States {
	template<typename T>
	class TransitionState : public State
	{
	public:
		
		TransitionState() = default;

		void onUpdate(Context &context) override
		{
			auto input = context.inputManager;
			if (menu->handleInput(context)) {
				return;
			}
		}

		void onEnter(Context & context) override
		{
			if (menu != nullptr) {
				menu = nullptr;
				menuBuilder = Menu::MenuBuilder();
			}

			menuBuilder.addControl(-0.5, 0.5, 1, 0.24, "img/loading.png");
			menu = menuBuilder.buildMenu();
			Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
			renderDevice->clearScreen();
			menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
			context.window->swapScreen();

			auto input = context.inputManager;
			if (menu->handleInput(context)) {
				return;
			}

			context.stateMachine->setState<T>();
		}

		void onLeave(Context &context) override {
			context.stateMachine->removeState<TransitionState<T>>();
		}


	private:
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;
	};
}

