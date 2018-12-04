#include "States/CreditsState.h"
#include "StateMachine.h";
#include "States/PrismGame.h"
#include "States/MainMenuState.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"

namespace States {
	CreditsState::CreditsState()
	{
	}

	void CreditsState::onInit(Context & context)
	{
		std::function<void()> callback = [&context]() { context.stateMachine->setState<MainMenuState>(context); };
		menuBuilder.addControl(-1, 0.4, 0.1, 0.1, "img/Back.png", callback);
		menuBuilder.addControl(-0.37f, -0.86f, 0.77f, 1.77f, "img/credits.png");

		menu = menuBuilder.buildMenu();
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void CreditsState::onUpdate(Context & context)
	{
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(menu, float(context.window->width) / float(context.window->height));
		context.window->swapScreen();

		auto input = context.inputManager;
		if (menu.handleInput(*context.inputManager, context.window->width, context.window->height)) {
			return;
		}
	}

	void CreditsState::onEnter(Context & context)
	{
	}

	void CreditsState::onLeave(Context & context)
	{
	}

	CreditsState::CreditsState(const CreditsState & obj)
	{
		menu = obj.menu;
	}

	CreditsState::~CreditsState()
	{
	}
}