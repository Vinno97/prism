#include "States/ResolutionMenuState.h"
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "States/CreditsState.h"
#include "States/HelpState.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Util/AdvertisementSystem.h"
#include <cstdlib>
#include <Variables.h>
#include "States/MainMenuState.h"

namespace States {
	using namespace Variables::Resources;


	void ResolutionMenuState::onInit(Context & context)
	{
		std::function<void()> callback = [&context]()
		{
			context.stateMachine->setState<MainMenuState>();
		};
		menuBuilder.addControl(-0.8f, 0.8, .25, 0.096, Sprites::BACK, [&context]() {
			context.stateMachine->setState<MainMenuState>();
		});
		menuBuilder.addControl(-0.35, 0.4, 0.6, 0.18, "img/resolutionoptions/960-720.png", [&context]() { context.window->setSize(960, 720); });
		menuBuilder.addControl(-0.35, 0.1, 0.6, 0.18, "img/resolutionoptions/1360-768.png", [&context]() { context.window->setSize(1360, 768); });
		menuBuilder.addControl(-0.35, -0.2, 0.6, 0.18, "img/resolutionoptions/1536-864.png", [&context]() { context.window->setSize(1536, 864); });
		menuBuilder.addControl(-0.35, -0.5, 0.6, 0.18, "img/resolutionoptions/1440-1080.png", [&context]() { context.window->setSize(1440, 1080); });
		menuBuilder.addControl(-0.35, -0.8, 0.6, 0.18, "img/resolutionoptions/1920-1080.png", [&context]() { context.window->setSize(1920, 1080); });

		menu = menuBuilder.buildMenu();

		renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void ResolutionMenuState::onUpdate(Context & context)
	{
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, context.window->width, context.window->height);

		menu->handleInput(context);

		context.window->swapScreen();
	}

	void ResolutionMenuState::onEnter(Context & context)
	{
		context.audioManager->playMusic("MainMenu");
	}

}
