#include "States/PauseState.h"
#include "StateMachine.h";
#include "States/PrismGame.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"

namespace States {
	PauseState::PauseState()
	{
	}

	void PauseState::onInit(Context & context)
	{
		menuBuilder.addControl(-0.5, 0, 1, 0.21, "img/pause.png");
		menu = menuBuilder.buildMenu();
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void PauseState::onUpdate(Context & context)
	{

		auto input = context.inputManager;
		if (input->isKeyPressed(Key::KEY_ESCAPE) && canPressEscape) {
			canPressEscape = false;
			context.stateMachine->setState<PrismGame>(context);
		}

		if (!input->isKeyPressed(Key::KEY_ESCAPE)) {
			canPressEscape = true;
		}

		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(menu, float(context.window->width) / float(context.window->height));
		context.window->swapScreen();
	}

	void PauseState::onEnter(Context & context)
	{

	}

	void PauseState::onLeave(Context & context)
	{
	}

	PauseState::PauseState(const PauseState & obj)
	{
		menu = obj.menu;
	}

	PauseState::~PauseState()
	{
	}
}