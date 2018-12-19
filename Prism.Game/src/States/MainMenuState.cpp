#include "States/MainMenuState.h"
#include "StateMachine.h";
#include "States/PrismGame.h"; 
#include "States/CreditsState.h"; 
#include "States/HighScoreState.h"; 
#include "States/HelpState.h"
#include "Math/Vector3f.h";
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Util/AdvertisementSystem.h"
#include <cstdlib>
#include "States/ResolutionMenuState.h"

using namespace Math;

namespace States {
	MainMenuState::MainMenuState()
	{
	}

	void MainMenuState::onInit(Context & context)
	{
		loadMusic(context);
		context.stateMachine->addState<CreditsState>(context);
		context.stateMachine->addState<ResolutionMenuState>(context);
		context.stateMachine->addState<HelpState>(context);
		context.stateMachine->addState<HighScoreState>(context);

		std::function<void()> callback = [&](){
			context.stateMachine->removeState<PrismGame>();
			context.stateMachine->addState<PrismGame>(context);
			context.stateMachine->setState<PrismGame>(context);
			if (nightmareMode) {
				context.stateMachine->getState<PrismGame>()->toggleNightmare(context);
			}
		};

		
		std::function<void()> nightmareModeCallback = [&]() { 
			if (cooldown > maxCooldown) {
				if (!nightmareMode) {
					context.audioManager->playSound("NightmareOn", 0);
					nightmareMode = true;
				}
				else {
					context.audioManager->playSound("NightmareOff", 0);
					nightmareMode = false;
				}
				cooldown = 0;
			}
		};

		std::function<void()> creditsCallback = [&context]() { context.stateMachine->setState<CreditsState>(context); };
		std::function<void()> settingsCallback = [&context]()
		{
			context.stateMachine->setState<ResolutionMenuState>(context);
		};
		std::function<void()> helpCallback = [&]() {context.stateMachine->setState<HelpState>(context); };
		std::function<void()> highscoreCallback = [&context]() {context.stateMachine->setState<HighScoreState>(context); };
		std::function<void()> quitCallback = [&]() {
			if (exitBool) {
				exit(0);
			}
			exitBool = true;
		};

		const float aspect = float(context.window->width) / float(context.window->height);
    
		menuBuilder.addControl(-0.35,  0.7, 0.6, 0.18, "img/NewGameButton.png", callback);
		menuBuilder.addControl(-0.35,  0.4, 0.6, 0.18, "img/LoadGameButton.png");
		menuBuilder.addControl(-0.35,  0.1, 0.6, 0.18, "img/ToCredits.png", creditsCallback);
		menuBuilder.addControl(-0.35, -0.2, 0.6, 0.18, "img/ToHelp.png", helpCallback);
		menuBuilder.addControl(-0.35, -0.5, 0.6, 0.18, "img/HighscoreButton.png", highscoreCallback);
		menuBuilder.addControl(-0.98, 0.9 , 0.05, 0.05*aspect, "img/settings.png", settingsCallback);
		menuBuilder.addControl(-0.35, -0.8, 0.6, 0.18, "img/QuitGameButton.png", quitCallback);
		menuBuilder.addControl(-0.7, 0.49, 0.35, 0.1, "img/nightmare_mode.png", nightmareModeCallback);

		menu = menuBuilder.buildMenu();
		renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void MainMenuState::onUpdate(Context & context)
	{
		cooldown += context.deltaTime;
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, context.window->width, context.window->height);

		auto input = context.inputManager;
		if (menu->handleInput(*context.inputManager, context.window->width, context.window->height, context)) {
			return;
		}

		context.window->swapScreen();
	}

	void MainMenuState::onEnter(Context & context)
	{
		context.audioManager->playMusic("MainMenu");
		nightmareMode = false;
	}

	void MainMenuState::onLeave(Context & context)
	{
 	}

	MainMenuState::~MainMenuState()
	{
	}
	void MainMenuState::loadMusic(Context & context)
	{
		context.audioManager->addMusic("MainMenu", "MainMenu.wav");
		context.audioManager->addSound("NightmareOn", "NightmareModeOn.wav");
		context.audioManager->addSound("NightmareOff", "NightmareModeOff.wav");
	}
}
