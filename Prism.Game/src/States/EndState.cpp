#include "States/EndState.h"
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "States/MainMenuState.h"
#include "States/EndState.h"
#include "States/PauseState.h"
#include "States/MainMenuState.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"

namespace States {
	EndState::EndState()
	{
	}

	void EndState::onInit(Context & context)
	{
		std::function<void()> callbackMainMenu = [&context](){ context.stateMachine->setState<MainMenuState>(context); };
		std::function<void()> callBackRestart = [&context](){
			if (!context.stateMachine->hasState<PrismGame>()) {
				context.stateMachine->addState<PrismGame>(context);
				context.stateMachine->setState<PrismGame>(context);

			}
		};

		menuBuilder.addControl(-0.5, 0.5, 1, 0.24, "img/gameover.png");

		menuBuilder.addControl(-0.35, 0.1, 0.7, 0.18, "img/mainMenuButton.png", callbackMainMenu);
		menuBuilder.addControl(-0.35, -0.2, 0.7, 0.18, "img/restart.png", callBackRestart);

		menu = menuBuilder.buildMenu();

		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void EndState::onUpdate(Context & context)
	{
	   	Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, float(context.window->width) / float(context.window->height));

		auto input = context.inputManager;
		if (menu->handleInput(*context.inputManager, context.window->width, context.window->height)) {
			return;
		}

		context.window->swapScreen();
	}

	void EndState::onEnter(Context & context)
	{
		context.stateMachine->removeState<PrismGame>();
	}

	void EndState::onLeave(Context & context)
	{
	}

	EndState::~EndState()
	{
	}
}