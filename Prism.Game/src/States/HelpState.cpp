#include "States/HelpState.h"
#include "Variables.h"
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "States/MainMenuState.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"

namespace States {
	using namespace Variables::Resources;

	void HelpState::onInit(Context & context)
	{
		menuBuilder.addControl(-0.8f, 0.8, .25, 0.096, Sprites::BACK, [&context]() {
			context.stateMachine->setState<MainMenuState>();
		});
		menuBuilder.addControl(-0.5f, 0.7f, 1.2f, 0.2f, "img/goal.png");
		menuBuilder.addControl(-1.f, -1.0f, 2.0f, 1.5f, "img/HelpScreen.jpg");

		menu = menuBuilder.buildMenu();
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void HelpState::onUpdate(Context & context) {
		Renderer::Graphics::RenderDevice *renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
		context.window->swapScreen();

        menu->handleInput(context);
	}
}