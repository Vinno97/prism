	#include <iostream>
#include <fstream>
#include "States/HighScoreState.h"
#include "StateMachine.h";
#include "States/PrismGame.h"
#include "States/MainMenuState.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"

namespace States {
	HighScoreState::HighScoreState()
	{
	}

	void HighScoreState::onInit(Context & context)
	{

	}

	void HighScoreState::onUpdate(Context & context)
	{
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, float(context.window->width), float(context.window->height));
		context.window->swapScreen();

		auto input = context.inputManager;
		if (menu->handleInput(*context.inputManager, context.window->width, context.window->height, context)) {
			return;
		}
	}

	void HighScoreState::onEnter(Context & context)
	{
		buildMenu(context);

	}

	void HighScoreState::buildMenu(Context & context) {
		if (menu != nullptr) {
			menu = nullptr;
			menuBuilder = Menu::MenuBuilder();
		}

		menuBuilder.addControl(-0.5, 0.5, 1, 0.24, "img/HighscoreButton.png");
		showHighscore(getHighScore(), context);
		std::function<void()> callback = [&context]() { context.stateMachine->setState<MainMenuState>(context); };
		menuBuilder.addControl(-0.9f, 0.8, 0.3, 0.1, "img/Back.png", callback);
		Renderer::Graphics::RenderDevice* renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
		menu = menuBuilder.buildMenu();
	}

	std::vector<int> HighScoreState::getHighScore()
	{
		std::ifstream infile;
		infile.open("res/saves/scores.txt");
		std::vector<int> numbers;

		if (infile.is_open())
		{
			int num;
			while (infile >> num)
			{
				numbers.push_back(num);
			}
		}


		// Sort list (high to low)
		std::sort(numbers.begin(), numbers.end());
		std::reverse(numbers.begin(), numbers.end());

		return numbers;
	}


	void HighScoreState::showHighscore(std::vector<int> numbers, Context & context) {
		int count = 1;
		double test = 0.3;

		for (auto const& value : numbers)
		{
			if (count == 6) {
				break;
			}
			menuBuilder.addControl(-0.35, test, 0.6, 0.18, "img/highScoreBackground.png");
			menuBuilder.addTextControl(-0.25, test + 0.05, 0.0013, Math::Vector3f{ 1.0f, 1.0f, 1.0f }, std::to_string(count) + ": " + std::to_string(value));
			count++;
			test -= 0.2;
		}
	}

	void HighScoreState::onLeave(Context & context)
	{
	}


	HighScoreState::~HighScoreState()
	{
	}
}