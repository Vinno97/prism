#include "States/WorldSelectionState.h"

#include <cmath>
#include <algorithm>
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

        Menu::MenuBuilder menuBuilder;
        menuBuilder.addControl(-0.5f, 0.5, 1, 0.24, Sprites::GAME_OVER);
        // TODO: Make a uniform GUI design with a standard location for this button.
        menuBuilder.addControl(-0.9f, 0.8, 0.3, 0.1, Sprites::BACK, [&context]() {
            context.stateMachine->setState<MainMenuState>(context);
        });

        constexpr auto width = (2 - OUTER_MARGIN * 2) / COLUMNS - GRID_MARGIN;
        constexpr auto height = (1.5f - OUTER_MARGIN * 2) / ROWS - GRID_MARGIN;

        // TODO: Draw these from top-left to bottom-right
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLUMNS; ++c) {
                const auto &levelName = levels[r * ROWS + c];
                const auto x = -1 + OUTER_MARGIN + c * (width + GRID_MARGIN);
                const auto y = -1 + OUTER_MARGIN + r * (height + GRID_MARGIN);
                const auto path = levelDirectory + '/' + levelName;
                const auto callback = [&context, path]() {
                    if (context.stateMachine->hasState<PrismGame>()) {
                        context.stateMachine->removeState<PrismGame>();
                    }
                    context.stateMachine->addState<PrismGame>(context, path);
                    context.stateMachine->setState<PrismGame>(context);
                };

                // TODO: Use proper button images
                // TODO: Show the level names
                if (levelName.empty()) {
                    menuBuilder.addControl(x, y, width, height, Sprites::NEW_GAME);
                } else {
                    menuBuilder.addControl(x, y, width, height, Sprites::GAME_OVER, callback);
                }
            }
        }

        renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
        renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);

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