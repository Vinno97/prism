#include "States/MainMenuState.h"
#include "StateMachine.h";
#include "States/PrismGame.h"; 
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"

namespace States {
	MainMenuState::MainMenuState()
	{
	}

	void MainMenuState::onInit(Context & context)
	{
		PrismGame game = PrismGame();
		context.stateMachine->addState(game, context);

		std::function<void()> callback = [context]() { context.stateMachine->setState<PrismGame>(); };
		menuBuilder.addControl(-0.35,  0.4, 0.6, 0.18, "img/NewGameButton.png", callback);
		menuBuilder.addControl(-0.35,  0.1, 0.6, 0.18, "img/LoadGameButton.png");
		menuBuilder.addControl(-0.35, -0.7, 0.6, 0.18, "img/QuitGameButton.png");

		menu = menuBuilder.buildMenu();
		renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void MainMenuState::onUpdate(Context & context)
	{
		renderDevice->clearScreen();
		menuRenderer.renderMenu(menu, float(context.window->width) / float(context.window->height));

		textRenderer.RenderText("1 Red resources", 0, 0, 0.001);

		auto input = context.inputManager;
		if (menu.handleInput(*context.inputManager, context.window->width, context.window->height)) {
			return;
		}

		context.window->swapScreen();
	}

	void MainMenuState::onEnter()
	{

	}

	void MainMenuState::onLeave()
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