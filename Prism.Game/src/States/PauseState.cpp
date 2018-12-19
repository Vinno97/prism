#include "States/PauseState.h"
#include "States/EndState.h"
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"

namespace States {
	void PauseState::onInit(Context & context)
	{
		std::function<void()> callbackEndstate = [&context]() { 
			context.stateMachine->setState<EndState>(context);			
		};

		menuBuilder.addControl(-0.5, 0, 1, 0.21, "img/pause.png");
		menuBuilder.addControl(-0.35, -0.5, 0.7, 0.18, "img/QuitGameButton.png", callbackEndstate);

		menu = menuBuilder.buildMenu();
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void PauseState::onUpdate(Context & context)
	{

		auto input = context.inputManager;
		if (input->isKeyPressed(Key::KEY_ESCAPE) && canPressEscape) {
			canPressEscape = false;
			context.stateMachine->setState<PrismGame>(context);
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