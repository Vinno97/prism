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
		std::function<void()> callback = [&context]() { context.stateMachine->setState<MainMenuState>(context); };
		std::function<void()> swapScreen = [&]() { swap(); };
		menuBuilder.addControl(-0.9f, 0.8, 0.30, 0.10, "img/Back.png", callback);
		menuBuilder.addControl(0.6f, 0.8, 0.30, 0.10, "img/Swap.png", swapScreen);
		control = menuBuilder.addImage(-1.0f, -1.0f, 2.0f, 1.6f, "img/SirHelpScreenII.png");
		menu = menuBuilder.buildMenu();
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void HelpState::onUpdate(Context & context) {
		menu->handleInput(context);
		Renderer::Graphics::RenderDevice *renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
		context.window->swapScreen();
		countDown += context.deltaTime;
		auto input = context.inputManager;
		

	}
	void HelpState::swap()
	{
		if(count == 1 && countDown > maxcountDown)
		{
			control->UpdateTexture("img/SirHelpScreenII.png");
			count = 0;
			countDown = 0;
		}else if(countDown > maxcountDown)
		{
			control->UpdateTexture("img/HelpScreen.png");
			count = 1;
			countDown = 0;
		}
	}
}