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
		menuBuilder.addControl(-0.5, 0, 1, 0.21, "img/pause.png", callback);
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