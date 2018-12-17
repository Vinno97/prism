#include "States/WorldSelectionState.h"

#include <cmath>
#include <algorithm>
#include <fmt/core.h>
#include <States/PrismGame.h>
#include <States/MainMenuState.h>
#include "StateMachine.h"
#include "Menu/MenuBuilder.h"
#include "Util/FileSystem.h"

using namespace Variables;
using namespace Variables::Resources;
using namespace Variables::Visual::LevelSelection;

namespace States {

    void WorldSelectionState::onInit(Context &context) {
        auto saves = Util::FileSystem().getFilenamesInDirectory(levelDirectory);
        saves.erase(std::remove_if(saves.begin(), saves.end(), [](const std::string &v) {
            constexpr std::string_view extension = LEVEL_EXTENSION;
            const auto canFit = extension.size() <= v.size();
            const auto matchesEnd = std::equal(v.begin() + v.size() - extension.size(), v.end(), extension.begin());
            return !(canFit && matchesEnd);
        }), saves.end());

        std::copy_n(saves.begin(), std::min(levels.size(), saves.size()), levels.begin());

        renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
        renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);

        makeButtons(context);
    }

    void WorldSelectionState::makeButtons(Context &context) {
        constexpr auto width = (2 - OUTER_MARGIN * 2) / COLUMNS - GRID_MARGIN;
        constexpr auto height = (1.5f - OUTER_MARGIN * 2) / ROWS - GRID_MARGIN;

        Menu::MenuBuilder menuBuilder;
        menuBuilder.addControl(-0.5f, 0.5, 1, 0.24, Sprites::GAME_OVER);
        // TODO: Make a uniform GUI design with a standard location for this button.
        menuBuilder.addControl(-0.9f, 0.8, 0.3, 0.1, Sprites::BACK, [&context]() {
            context.stateMachine->setState<MainMenuState>(context);
        });


        const auto pageCount = std::ceil(1.0 * levels.size() / pageSize) + 1;
        const auto pageStr = fmt::format("{:^25}", fmt::format("{} / {}", currentPage + 1,
                                                               pageCount));
        menuBuilder.addTextControl(-.25f, -.95f, 0.001f, Math::Vector3f(0, 0, 0), pageStr);

        if (currentPage > 0) {
            menuBuilder.addControl(-0.4f, -.95f, 0.1, 0.1, Sprites::LEVEL_SLOT_FILLED, [&]() {
                currentPage -= 1;
                makeButtons(context);
            });
        } else {
            menuBuilder.addControl(-0.4f, -.95f, 0.1, 0.1, Sprites::LEVEL_SLOT_EMPTY);
        }

        if (currentPage < pageCount - 1) {
            menuBuilder.addControl(0.3f, -.95f, 0.1, 0.1, Sprites::LEVEL_SLOT_FILLED, [&]() {
                currentPage += 1;
                makeButtons(context);
            });
        } else {
            menuBuilder.addControl(0.3f, -.95f, 0.1, 0.1, Sprites::LEVEL_SLOT_EMPTY);
        }


        const int pageOffset = currentPage * COLUMNS * ROWS;
        // TODO: Draw these from top-left to bottom-right
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLUMNS; ++c) {
                const auto levelIndex = pageOffset + r * ROWS + c;

                const auto x = -1 + OUTER_MARGIN + c * (width + GRID_MARGIN);// + -.045 * r;
                const auto y = -1 + OUTER_MARGIN + (ROWS - 1 - r) * (height + GRID_MARGIN);

                // TODO: Use proper button images
                // TODO: Show the level names
                if (levels.size() > levelIndex) {
                    const auto levelName = levels[levelIndex];
                    const auto path = levelDirectory + '/' + levelName;
                    const auto readableLevelName = levelName.substr(0, levelName.find(".json"));
                    menuBuilder.addControl(x, y, width, height, Sprites::LEVEL_SLOT_FILLED, [&context, path]() {
                        if (context.stateMachine->hasState<PrismGame>()) {
                            context.stateMachine->removeState<PrismGame>();
                        }
                        context.stateMachine->addState<PrismGame>(context, path);
                        context.stateMachine->setState<PrismGame>(context);
                    });
                    menuBuilder.addControl(x, y, width, height, Sprites::LEVEL_SLOT_FILLED);
                    menuBuilder.addTextControl(x + .03f, y + height / 2, 0.001, Math::Vector3f(1, 1, 1),
                                               fmt::format("{:^13}", readableLevelName));
                } else {
                    menuBuilder.addControl(x, y, width, height, Sprites::LEVEL_SLOT_EMPTY);

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
        menuRenderer.renderMenu(*menu, float(context.window->width) / float(context.window->height));

        auto input = context.inputManager;
        if (menu->handleInput(*context.inputManager, context.window->width, context.window->height)) {
            return;
        }

        context.window->swapScreen();
    }

}