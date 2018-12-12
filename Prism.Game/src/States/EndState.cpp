#include "States/EndState.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "States/MainMenuState.h"
#include "States/EndState.h"
#include "States/PauseState.h"
#include "States/MainMenuState.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/ScoreComponent.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"

namespace States {
	using namespace ECS;
	using namespace ECS::Components;

	EndState::EndState()
	{
	}

	void EndState::onInit(Context & context)
	{
		survivedTimeLabel = menuBuilder.addTextControl(-0.98, -0.4, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "Time survived:");
		killedEnemiesLabel = menuBuilder.addTextControl(-0.98, -0.45, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "Kills:");
		redLabel = menuBuilder.addTextControl(-0.98, -0.50, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "Red resources:");
		blueLabel = menuBuilder.addTextControl(-0.98, -0.55, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "Blue resources:");
		greenLabel = menuBuilder.addTextControl(-0.98, -0.60, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "Green resources:");
		scoreLabel = menuBuilder.addTextControl(-0.98, -0.65, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "Total score:");

		survivedTime = menuBuilder.addTextControl(-0.5, -0.4, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		killedEnemies = menuBuilder.addTextControl(-0.5, -0.45, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		red = menuBuilder.addTextControl(-0.5, -0.50, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		blue = menuBuilder.addTextControl(-0.5, -0.55, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		green = menuBuilder.addTextControl(-0.5, -0.60, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		score = menuBuilder.addTextControl(-0.5, -0.65, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");

		std::function<void()> callbackMainMenu = [&context]() { context.stateMachine->setState<MainMenuState>(context); };
		std::function<void()> callBackRestart = [&]() {
			if (!context.stateMachine->hasState<PrismGame>()) {
				context.stateMachine->addState<PrismGame>(context);
				context.stateMachine->setState<PrismGame>(context);

			}
		};

		menuBuilder.addControl(-0.5, 0.5, 1, 0.24, "img/gameover.png");
		menuBuilder.addControl(-1, -.35, 0.7, 0.08, "img/stats.png");
		menuBuilder.addControl(-0.35, 0.1, 0.7, 0.18, "img/mainMenuButton.png", callbackMainMenu);
		menuBuilder.addControl(-0.35, -0.2, 0.7, 0.18, "img/restart.png", callBackRestart);
		menu = menuBuilder.buildMenu();

		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void EndState::onUpdate(Context & context)
	{
		score->text = std::to_string(totalscore);
		survivedTime->text = std::to_string(time);
		red->text = std::to_string(resourceRed);
		blue->text = std::to_string(resourceBlue);
		green->text = std::to_string(resourceGreen);
		killedEnemies->text = std::to_string(kills);
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, float(context.window->width) / float(context.window->height));

		auto input = context.inputManager;
		if (menu->handleInput(*context.inputManager, context.window->width, context.window->height)) {
			return;
		}

		context.window->swapScreen();
	}

	void EndState::onEnter(Context & context)
	{
		context.stateMachine->removeState<PrismGame>();

		std::fstream file;
		std::vector<int> numbers;
		int newScore = totalscore;
		file.open("res/saves/scores.txt", std::fstream::in | std::fstream::out | std::fstream::app);

		if (file.is_open())
		{
			if (file.peek() == std::ifstream::traits_type::eof()) {
				numbers.push_back(newScore);
			}
			else {
				int count = 0;
				int num;
				while (file >> num)
				{
					if (count == 5) {
						break;
					}

					if (newScore >= num) {
						numbers.push_back(newScore);
						newScore = 0;
						count++;
					}
					
					if(count < 5) {
						numbers.push_back(num);
						count++;
					}
				}

				if (count <= 4 && newScore != 0) {
					numbers.push_back(newScore);
				}
			}

			std::sort(numbers.begin(), numbers.end());
			std::reverse(numbers.begin(), numbers.end());

			std::ofstream out("res/saves/scores.txt", std::ios_base::trunc);

			if (out.is_open()) {
				std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(out, "\n"));
			}

		}
	}

	void EndState::onLeave(Context & context)
	{
	}

	EndState::~EndState()
	{
	}
}