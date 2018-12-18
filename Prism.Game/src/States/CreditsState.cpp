#include "States/CreditsState.h"
#include "Variables.h"
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "States/MainMenuState.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Util/AdvertisementSystem.h"

namespace States {
	using namespace Variables::Resources;

	void CreditsState::onInit(Context & context)
	{
		menuBuilder.addControl(-0.8f, 0.8, .25, 0.096, Sprites::BACK, [&context]() {
			context.stateMachine->setState<MainMenuState>(context);
		});
		menuBuilder.addControl(-0.37f, -0.86f, 0.7, 1.777f, "img/credits.png");

		Util::AdvertisementSystem as;
		std::string filepath = "img/advertisements/" + as.RandomAdvertisement();
		menuBuilder.addControl(0.55f, -1, 0.25, (1.777f / 4.0f), filepath.c_str());

		menu = menuBuilder.buildMenu();
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void CreditsState::onUpdate(Context & context)
	{
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
		context.window->swapScreen();

		if (menu->handleInput(*context.inputManager, context.window->width, context.window->height)) {
			return;
		}
	}
}