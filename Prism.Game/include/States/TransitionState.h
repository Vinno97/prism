#pragma once

#include <memory>
#include "State.h"
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
			menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
			context.window->swapScreen();

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

			menuBuilder.addControl(-0.9f, 0.8, 0.3, 0.1, "img/Back.png");
			menu = menuBuilder.buildMenu();
			Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
			renderDevice->clearScreen();
			menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
			context.window->swapScreen();

			auto input = context.inputManager;
			if (menu->handleInput(context)) {
				return;
			}

			context.stateMachine->setState<T>(context);
		}


	private:
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;
	};
}

