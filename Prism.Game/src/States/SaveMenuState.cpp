#include "States/SaveMenuState.h"

#include <cmath>
#include <algorithm>
#include <fmt/core.h>
#include <States/PauseState.h>
#include <States/MainMenuState.h>
#include "StateMachine.h"
#include "Menu/MenuBuilder.h"
#include "Util/FileSystem.h"
#include "States/PrismGame.h"
#include <ctime>
#include <chrono>


using namespace Variables;
using namespace Variables::Resources;
using namespace Variables::Visual::LevelSelection;

namespace States
{
	void SaveMenuState::onInit(Context& context)
	{
		ASPECT = context.window->width / context.window->height;


		renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);

		makeButtons(context);
	}

	void SaveMenuState::onUpdate(Context& context)
	{
		// TODO: Move this generic code to shared function or superclass.
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
		if (menu->handleInput(*context.inputManager, context.window->width, context.window->height)) {
			return;
		}

		context.window->swapScreen();
	}

	void SaveMenuState::makeButtons(Context& context)
	{
		savedGames = Util::FileSystem().getFilenamesInDirectory(levelDirectory);
		savedGames.erase(std::remove_if(savedGames.begin(), savedGames.end(), [](const std::string &v) {
			const std::string extension = LEVEL_EXTENSION;
			const auto canFit = extension.size() <= v.size();
			const auto matchesEnd = std::equal(v.begin() + v.size() - extension.size(), v.end(), extension.begin());
			return !(canFit && matchesEnd);
		}), savedGames.end());

		constexpr auto width{ (2 - OUTER_MARGIN * 2) / COLUMNS - GRID_MARGIN };
		constexpr auto height{ (1.5f - OUTER_MARGIN * 2) / ROWS - GRID_MARGIN };
		Menu::MenuBuilder menuBuilder;

		menuBuilder.addControl(-0.5f, 0.5, 1, 0.24, Sprites::GAME_OVER);
		// TODO: Make a uniform GUI design with a standard location for this button.
		menuBuilder.addControl(-0.9f, 0.8, 0.3, 0.1, Sprites::BACK, [&context]() {
			context.stateMachine->setState<PauseState>(context);
		});

		const auto pageCount{ std::ceil(1.0 * savedGames.size() / pageSize) };
		const auto pageStr{ fmt::format("{: ^7}", fmt::format("{} / {}", currentPage + 1, pageCount)) };
		menuBuilder.addTextControl(-.08f, -.95f, 0.001f, Math::Vector3f(0, 0, 0), pageStr);

		if (currentPage > 0) {
			menuBuilder.addControl(-0.32f, -.95f, 0.05, 0.080, Sprites::PREVIOUS_BUTTON, [&]() {
				currentPage -= 1;
				makeButtons(context);
			});
		}
		else {
			menuBuilder.addControl(-0.32f, -.95f, 0.05, 0.080, Sprites::PREVIOUS_BUTTON_DISABLED);
		}

		if (currentPage < pageCount - 1) {
			menuBuilder.addControl(0.24f, -.95f, 0.05, 0.080, Sprites::NEXT_BUTTON, [&]() {
				currentPage += 1;
				makeButtons(context);
			});
		}
		else {
			menuBuilder.addControl(0.24f, -.95f, 0.05, 0.080, Sprites::NEXT_BUTTON_DISABLED);
		}


		const int pageOffset{ currentPage * COLUMNS * ROWS };
		// TODO: Draw these from top-left to bottom-right
		for (int r{ 0 }; r < ROWS; ++r) {
			for (int c = 0; c < COLUMNS; ++c) {
				const auto levelIndex = pageOffset + r * COLUMNS + c;

				const auto x{ -1 + OUTER_MARGIN + c * (width + GRID_MARGIN) };
				const auto y{ -1 + OUTER_MARGIN + (ROWS - 1 - r) * (height + GRID_MARGIN) };

				if (savedGames.size() > levelIndex) {
					const auto levelName{ savedGames[levelIndex] };
					const auto path{ levelDirectory + '/' + levelName };
					std::string readableLevelName{ levelName.substr(0, levelName.find(".json")) };
					
					menuBuilder.addControl(x, y, width, height, Sprites::LEVEL_SLOT_FILLED, [&, path]() {
						if (context.stateMachine->hasState<PrismGame>()) {
							context.stateMachine->getState<PrismGame>()->Save(path);
	
							context.stateMachine->setState<PauseState>(context);
							makeButtons(context);
						}
					});
					readableLevelName = fmt::format("{:^13}", readableLevelName);
					if (readableLevelName.size() > 13)
						readableLevelName = readableLevelName.substr(0, 10) + "...";

					menuBuilder.addControl(x, y, width, height, Sprites::LEVEL_SLOT_FILLED);
					menuBuilder.addTextControl(x + .03f, y + height / 2, 0.001, Math::Vector3f(1, 1, 1),
						readableLevelName);
				}
				else {
					menuBuilder.addControl(x, y, width, height, Sprites::LEVEL_SLOT_EMPTY, [&]()
					{
						if (context.stateMachine->hasState<PrismGame>()) {
							std::chrono::system_clock::time_point p = std::chrono::system_clock::now();

							std::time_t t = std::chrono::system_clock::to_time_t(p);

							std::string saveGameName = std::to_string(t);
							std::string save  = "saves/" + saveGameName + LEVEL_EXTENSION;
							context.stateMachine->getState<PrismGame>()->Save(save);

							context.stateMachine->setState<PauseState>(context);
							makeButtons(context);
						}
					});

					menuBuilder.addControl(x + .025f, y + height / 4 + .09f, width - 0.05f, .11,
						Sprites::WHITE_BORDERED);

					menuBuilder.addTextControl(x + .05f, y + height / 2, 0.001, Math::Vector3f(0, 0, 0), "Empty Slot");
				}

			}
		}
		menu = menuBuilder.buildMenu();
	}
}
