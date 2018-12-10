#include "States/SelectLevelState.h"

#include <cmath>
#include <algorithm>
#include <States/PrismGame.h>
#include "StateMachine.h"
#include "Menu/MenuBuilder.h"
#include "Util/FileSystem.h"

using namespace Variables::Visual::LevelSelection;
using namespace Variables::Resources;

namespace States {

    void SelectLevelState::onInit(Context &context) {
        auto saves = Util::FileSystem().getFilenamesInDirectory(levelDirectory);
        saves.erase(std::remove_if(saves.begin(), saves.end(), [](const std::string &v) {
            constexpr std::string_view extension = LEVEL_EXTENSION;
            const auto canFit = extension.size() <= v.size();
            const auto matchesEnd = std::equal(v.begin() + v.size() - extension.size(), v.end(), extension.begin());
            return !(canFit && matchesEnd);
        }), saves.end());

        std::copy_n(saves.begin(), std::min(levels.size(), saves.size()), levels.begin());

        Menu::MenuBuilder menuBuilder;

        constexpr auto width = (2 - OUTER_MARGIN * 4) / COLUMNS;
        constexpr auto height = (2 - OUTER_MARGIN * 4) / ROWS;

        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLUMNS; ++c) {
                const auto &levelName = levels[r * ROWS + c];

                if (!levelName.empty()) {
                    const auto x = -1 + OUTER_MARGIN + c * (width + GRID_MARGIN);
                    const auto y = -1 + OUTER_MARGIN + r * (height + GRID_MARGIN);
                    const auto path = levelDirectory + '/' + levelName;

                    menuBuilder.addControl(x, y, width, height, "img/NewGameButton.png", [&context, path]() {
                        if (context.stateMachine->hasState<PrismGame>()) {
                            context.stateMachine->removeState<PrismGame>();
                        }
                        context.stateMachine->addState<PrismGame>(context, path);
                        context.stateMachine->setState<PrismGame>(context);
                    });
                }
            }
        }

        renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
        renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);

        menu = menuBuilder.buildMenu();

    }

    void SelectLevelState::onUpdate(Context &context) {
        renderDevice->clearScreen();
        menuRenderer.renderMenu(*menu, float(context.window->width) / float(context.window->height));

        auto input = context.inputManager;
        if (menu->handleInput(*context.inputManager, context.window->width, context.window->height)) {
            return;
        }

        context.window->swapScreen();
    }

}