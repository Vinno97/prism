#include "States/MainMenuState.h"
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
	MainMenuState::MainMenuState()
	{
	}

	void MainMenuState::onInit(Context & context)
	{
		context.stateMachine->addState<PrismGame>(context);
		context.stateMachine->addState<CreditsState>(context);
		context.stateMachine->addState<HelpState>(context);

		std::function<void()> callback = [&context](){
			if (!context.stateMachine->hasState<PrismGame>()) {
				PrismGame newGame = PrismGame();
				context.stateMachine->addState<PrismGame>(context);
			}
			context.stateMachine->setState<PrismGame>(context);
		};
		std::function<void()> creditsCallback = [&context]() { context.stateMachine->setState<CreditsState>(context); };
		std::function<void()> helpCallback = [&]() {context.stateMachine->setState<HelpState>(context); };
		std::function<void()> quitCallback = [&]() {
			if (exitBool) {
				exit(0);
			}
			exitBool = true;
		};
    
		menuBuilder.addControl(-0.35,  0.4, 0.6, 0.18, "img/NewGameButton.png", callback);
		menuBuilder.addControl(-0.35,  0.1, 0.6, 0.18, "img/LoadGameButton.png");
		menuBuilder.addControl(-0.35, -0.2, 0.6, 0.18, "img/ToCredits.png", creditsCallback);
		menuBuilder.addControl(-0.35, -0.5, 0.6, 0.18, "img/ToHelp.png", helpCallback);
		menuBuilder.addControl(-0.35, -0.8, 0.6, 0.18, "img/QuitGameButton.png", quitCallback);

		menu = menuBuilder.buildMenu();
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void MainMenuState::onUpdate(Context & context)
	{
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(menu, float(context.window->width) / float(context.window->height));

		auto input = context.inputManager;
		if (menu.handleInput(*context.inputManager, context.window->width, context.window->height)) {
			return;
		}

		context.window->swapScreen();
	}

	void MainMenuState::onEnter(Context & context)
	{
		context.audioManager->playMusic("MainMenu");
	}

	void MainMenuState::onLeave(Context & context)
	{
 	}

	MainMenuState::MainMenuState(const MainMenuState & obj)
	{
		menu = obj.menu;
	}

	MainMenuState::~MainMenuState()
	{
	}
}