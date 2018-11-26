#include "States/MainMenuState.h"
#include "StateMachine.h";
#include "States/PrismGame.h"; 
#include "Math/Vector3f.h";
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"

using namespace Math;

namespace States {
	MainMenuState::MainMenuState()
	{
	}

	void MainMenuState::onInit(Context & context)
	{
		PrismGame game = PrismGame();
		context.stateMachine->addState(game, context);

		std::function<void()> callback = [context]() { context.stateMachine->setState<PrismGame>(); };
		std::function<void(Vector3f& position, Vector3f& size)> hoverCallback = [](Vector3f& position, Vector3f& size) { position.y -= 0.01; };
		std::function<void(Vector3f& position, Vector3f& size)> leaveCallback = [](Vector3f& position, Vector3f& size) { position.y += 0.01; };
		menuBuilder.addControl(-0.35,  0.4, 0.6, 0.18, "img/NewGameButton.png", callback, hoverCallback, leaveCallback);
		menuBuilder.addControl(-0.35,  0.1, 0.6, 0.18, "img/LoadGameButton.png", hoverCallback, leaveCallback);
		menuBuilder.addControl(-0.35, -0.7, 0.6, 0.18, "img/QuitGameButton.png", hoverCallback, leaveCallback);


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
		context.window->swapScreen();
		if (menu.handleInput(*context.inputManager, context.window->width, context.window->height)) {
			return;
		}

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