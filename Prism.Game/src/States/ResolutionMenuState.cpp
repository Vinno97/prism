#include "States/ResolutionMenuState.h"
#include "StateMachine.h";
#include "States/PrismGame.h"; 
#include "States/CreditsState.h"; 
#include "States/HelpState.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Util/AdvertisementSystem.h"
#include <cstdlib>

namespace States {
	ResolutionMenuState::ResolutionMenuState()
	{
	}

	void ResolutionMenuState::onInit(Context & context)
	{
		context.stateMachine->addState<PrismGame>(context);
		context.stateMachine->addState<CreditsState>(context);
		context.stateMachine->addState<HelpState>(context);

		std::function<void()> setRes1 = [&context]() { };

		menuBuilder.addControl(-0.35, 0.4, 0.6, 0.18, "img/NewGameButton.png", setRes1);
		menuBuilder.addControl(-0.35, 0.1, 0.6, 0.18, "img/LoadGameButton.png", setRes1);
		menuBuilder.addControl(-0.35, -0.2, 0.6, 0.18, "img/ToCredits.png", setRes1);
		menuBuilder.addControl(-0.35, -0.5, 0.6, 0.18, "img/ToHelp.png", setRes1);
		menuBuilder.addControl(-0.35, -0.8, 0.6, 0.18, "img/QuitGameButton.png", setRes1);

		menu = menuBuilder.buildMenu();

		renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void ResolutionMenuState::onUpdate(Context & context)
	{
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, float(context.window->width) / float(context.window->height));


		auto input = context.inputManager;
		if (menu->handleInput(*context.inputManager, context.window->width, context.window->height)) {
			return;
		}

		context.window->swapScreen();
	}

	void ResolutionMenuState::onEnter(Context & context)
	{
		context.audioManager->playMusic("MainMenu");
	}

	void ResolutionMenuState::onLeave(Context & context)
	{
	}

	ResolutionMenuState::~ResolutionMenuState()
	{
	}
}