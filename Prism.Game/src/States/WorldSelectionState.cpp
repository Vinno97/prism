#include "States/WorldSelectionState.h"

#include <cmath>
#include <algorithm>
#include <fmt/core.h>
#include <States/PrismGame.h>
#include <States/TransitionState.h>
#include <States/MainMenuState.h>
#include "StateMachine.h"
#include "Menu/MenuBuilder.h"
#include "Util/FileSystem.h"

using namespace Variables;
using namespace Variables::Resources;
using namespace Variables::Resources::Sprites;
using namespace Variables::Resources::Sprites::WorldSelection;
using namespace Variables::Visual::WorldSelection;

namespace States {

	void WorldSelectionState::onInit(Context &context) {
		renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
	}

	void WorldSelectionState::drawMenu(Context &context) {
		constexpr auto width{(2 - OUTER_MARGIN * 2) / COLUMNS - GRID_MARGIN};
		constexpr auto height{(1.5f - OUTER_MARGIN * 2) / ROWS - GRID_MARGIN};

		const SpritePath selectLevel = nightmareMode ? NightMare::SELECT_LEVEL : SELECT_LEVEL;
		const SpritePath back = nightmareMode ? NightMare::BACK : BACK;
		const SpritePath levelSlotFilled = nightmareMode ? NightMare::LEVEL_SLOT_FILLED : LEVEL_SLOT_FILLED;
		const SpritePath levelSlotEmpty = nightmareMode ? NightMare::LEVEL_SLOT_EMPTY : LEVEL_SLOT_EMPTY;
		const SpritePath nightMareBtn = nightmareMode ? NightMare::BTN_NIGHTMARE_MODE : BTN_NIGHTMARE_MODE;
		const SpritePath previousButton = nightmareMode ? NightMare::PREVIOUS_BUTTON : PREVIOUS_BUTTON;
		const SpritePath previousButtonDisabled = nightmareMode ? NightMare::PREVIOUS_BUTTON_DISABLED : PREVIOUS_BUTTON_DISABLED;
		const SpritePath nextButton = nightmareMode ? NightMare::NEXT_BUTTON : NEXT_BUTTON;
		const SpritePath nextButtonDisabled = nightmareMode ? NightMare::NEXT_BUTTON_DISABLED : NEXT_BUTTON_DISABLED;
		const Math::Vector3f textColor = nightmareMode ? Math::Vector3f(1, 1, 1) : Math::Vector3f(0, 0, 0);
		const Math::Vector3f buttonTextColor = nightmareMode ? Math::Vector3f(0, 0, 0) : Math::Vector3f(1, 1, 1);

		const auto refresh = [&](std::function<void()> f) {
			return [&, f]() {
				f();
				drawMenu(context);
			};
		};

		if (nightmareMode) renderDevice->setClearColour(0.f, 0.f, 0.f, 1.f);
		else renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);


		Menu::MenuBuilder menuBuilder;
		menuBuilder.addControl(-0.5f, 0.5, 1, 0.24, selectLevel);
		// TODO: Make a uniform GUI design with a standard location for this button.
		menuBuilder.addControl(-0.8f, 0.8, .25, 0.096, back, [&context]() {
			context.stateMachine->setState<MainMenuState>();
		});

		menuBuilder.addControl(-.04f, 0.36, 0.4, 0.096, nightMareBtn, refresh([&]() {
			nightmareMode = !nightmareMode;
			context.audioManager->playSound(nightmareMode ? "NightmareOn" :"NightmareOff", 0);
		}));


		const auto pageCount{std::ceil(1.0 * levels.size() / pageSize)};
		const auto pageStr{fmt::format("{: ^7}", fmt::format("{} / {}", currentPage + 1, pageCount))};
		menuBuilder.addTextControl(-.08f, -.95f, 0.001f, textColor, pageStr);

		if (currentPage > 0) {
			menuBuilder.addControl(-0.32f, -.95f, 0.05, 0.080, previousButton,
			                       refresh([&]() { currentPage -= 1; }));
		} else {
			menuBuilder.addControl(-0.32f, -.95f, 0.05, 0.080, previousButtonDisabled);
		}

		if (currentPage < pageCount - 1) {
			menuBuilder.addControl(0.24f, -.95f, 0.05, 0.080, nextButton,
			                       refresh([&]() { currentPage += 1; }));
		} else {
			menuBuilder.addControl(0.24f, -.95f, 0.05, 0.080, nextButtonDisabled);
		}


		const int pageOffset{currentPage * COLUMNS * ROWS};
		// TODO: Draw these from top-left to bottom-right
		for (int r{0}; r < ROWS; ++r) {
			for (int c = 0; c < COLUMNS; ++c) {
				const auto levelIndex = pageOffset + r * COLUMNS + c;

				const auto x{-1 + OUTER_MARGIN + c * (width + GRID_MARGIN)};
				const auto y{-1 + OUTER_MARGIN + (ROWS - 1 - r) * (height + GRID_MARGIN)};

				if (levels.size() > levelIndex) {
					const auto levelName{levels[levelIndex]};
					const auto path{levelDirectory + '/' + levelName};
					std::string readableLevelName{levelName.substr(0, levelName.find(".json"))};
					menuBuilder.addControl(x, y, width, height, levelSlotFilled, [&, path]() {
						if (context.stateMachine->hasState<PrismGame>()) {
							context.stateMachine->removeState<PrismGame>();
						}
						context.stateMachine->addState<PrismGame>(path, nightmareMode);
						context.stateMachine->addState<TransitionState<PrismGame>>();
						context.stateMachine->setState<TransitionState<PrismGame>>();
					});
					readableLevelName = fmt::format("{:^13}", readableLevelName);
					if (readableLevelName.size() > 13)
						readableLevelName = readableLevelName.substr(0, 10) + "...";

					menuBuilder.addControl(x, y, width, height, levelSlotFilled);
					menuBuilder.addTextControl(x + .03f, y + height / 2, 0.001, buttonTextColor,
					                           readableLevelName);
				} else {
					menuBuilder.addControl(x, y, width, height, levelSlotEmpty);
					menuBuilder.addControl(x + .025f, y + height / 4 + .09f, width - 0.05f, .11,
					                       Sprites::WHITE_BORDERED);
					menuBuilder.addTextControl(x + .05f, y + height / 2, 0.001, Math::Vector3f(0, 0, 0), "Empty Slot");
				}

			}
		}
		menu = menuBuilder.buildMenu();
	}

	void WorldSelectionState::onUpdate(Context &context) {
		// TODO: Move this generic code to shared function or superclass.
		renderDevice->clearScreen();
		menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
		menu->handleInput(context);

		context.window->swapScreen();
	}

	void WorldSelectionState::onLeave(Context &context) {
		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void WorldSelectionState::onEnter(Context &context) {
		levels = Util::FileSystem().getFilenamesInDirectory(levelDirectory);
		levels.erase(std::remove_if(levels.begin(), levels.end(), [](const std::string &v) {
			const std::string extension = LEVEL_EXTENSION;
			const auto canFit = extension.size() <= v.size();
			const auto matchesEnd = std::equal(v.begin() + v.size() - extension.size(), v.end(), extension.begin());
			return !(canFit && matchesEnd);
		}), levels.end());

		drawMenu(context);
	}


}