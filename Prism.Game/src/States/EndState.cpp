#include "States/EndState.h"
#include "StateMachine.h";
#include "States/PrismGame.h"; 
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
	}

	void EndState::onUpdate(Context & context)
	{
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(menu, float(context.window->width) / float(context.window->height));
		context.window->swapScreen();
	}

	void EndState::onEnter()
	{
		menuBuilder.addControl(0, 0, 1, 0.17, "img/gameover.png");
		menu = menuBuilder.buildMenu();
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void EndState::onLeave()
	{
	}

	EndState::EndState(const EndState & obj)
	{
		menu = obj.menu;
	}

	EndState::~EndState()
	{
	}
}