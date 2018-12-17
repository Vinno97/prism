#pragma once

#include <utility>
#include <string>
#include <array>

#include <State.h>
#include <Variables.h>
#include <Menu/Menu.h>
#include <Menu/MenuRenderer.h>

namespace States {
    class WorldSelectionState : public State {
    public:
        explicit WorldSelectionState(std::string levelDirectory) : levelDirectory(std::move(levelDirectory)) {};

        void onInit(Context &context) override;

        void onUpdate(Context &context) override;

    protected:
        void makeButtons(Context& context);

    private:
        std::unique_ptr<Menu::Menu> menu;
        Menu::MenuRenderer menuRenderer;
        std::string levelDirectory;
        std::vector<std::string> levels{""};
        Renderer::Graphics::RenderDevice *renderDevice{nullptr};
        int currentPage{0};
        static constexpr int pageSize{Variables::Visual::LevelSelection::ROWS * Variables::Visual::LevelSelection::COLUMNS};
    };
}