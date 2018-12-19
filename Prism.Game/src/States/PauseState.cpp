#include "States/PauseState.h"
#include "States/EndState.h"
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "States/SaveMenuState.h"

namespace States {
	void PauseState::onInit(Context & context)
	{
		ASPECT = context.window->width / context.window->height;

		if (!context.stateMachine->hasState<SaveMenuState>()) {
			context.stateMachine->addState<SaveMenuState>();
		}

		std::function<void()> callbackEndstate = [&context]() { 
			context.stateMachine->setState<EndState>();
		};

		std::function<void()> callbackSaveMenuState = [&context]() {
			context.stateMachine->setState<SaveMenuState>();
		};

		menuBuilder.addControl(-0.5, 0, 1 * ASPECT, 0.21, "img/pause.png");
		menuBuilder.addControl(-0.35, -0.5, 0.7 * ASPECT, 0.18, "img/QuitGameButton.png", callbackEndstate);
		menuBuilder.addControl(-0.35, -0.75, 0.7 * ASPECT, 0.18, "img/QuitGameButton.png", callbackSaveMenuState);

		menu = menuBuilder.buildMenu();
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
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

		if (menu->handleInput(context)) {
			canPressEscape = false;
			return;
		}

		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
		context.window->swapScreen();
	}

	void PauseState::onEnter(Context & context)
	{
		canPressEscape = false;
	}
}
