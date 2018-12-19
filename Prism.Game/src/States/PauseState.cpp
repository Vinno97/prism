#include "States/PauseState.h"
#include "States/EndState.h"
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "Variables.h"
#include "States/HelpState.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"

namespace States {
	using namespace Variables::Resources;
	using namespace Variables::Visual::MainMenu;

	void PauseState::onInit(Context & context)
	{
		std::function<void()> callbackEndstate = [&context]() { 
			context.stateMachine->setState<EndState>();
		};

		std::function<void()> callbackResume = [&context]() {
			context.stateMachine->setState<PrismGame>();
		};

		std::function<void()> callbackHelp = [&context]() {
			context.stateMachine->setState<HelpState>();
		};

		const float aspect = float(context.window->width) / float(context.window->height);
		const auto btnHeight = MENU_HEIGHT * aspect;
		auto y = .7f;
		auto s = MENU_MARGIN + MENU_HEIGHT;
		menuBuilder.addControl(-0.5f, y -= s, 1, 0.24, Sprites::Pause::PAUSE);

		menuBuilder.addControl(-0.35, y -= s + SPACE, MENU_WIDTH, btnHeight, Sprites::MainMenu::HELP, callbackHelp);
		menuBuilder.addControl(-0.35, y -= s, MENU_WIDTH, btnHeight, Sprites::Pause::RESUME, callbackResume);
		menuBuilder.addControl(-0.35, y -= s, MENU_WIDTH, btnHeight, Sprites::MainMenu::QUIT, callbackEndstate);
		menu = menuBuilder.buildMenu();
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void PauseState::onUpdate(Context & context)
	{

		auto input = context.inputManager;
		if (input->isKeyPressed(Key::KEY_ESCAPE) && canPressEscape) {
			canPressEscape = false;
			context.stateMachine->setState<PrismGame>();
		}

		if (!input->isKeyPressed(Key::KEY_ESCAPE)) {
			canPressEscape = true;
		}

		if (menu->handleInput(context)) {
			canPressEscape = false;
			return;
		}

		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
		context.window->swapScreen();
	}

	void PauseState::onEnter(Context & context)
	{
		canPressEscape = false;
	}
}