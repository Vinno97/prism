#include <utility>

#include <utility>

#include <utility>

#pragma once

#include <string>
#include <array>

#include <State.h>
#include <Variables.h>
#include <Menu/Menu.h>
#include <Menu/MenuRenderer.h>

namespace States {
    class SelectLevelState : public State {
    public:
        explicit SelectLevelState(std::string levelDirectory) : levelDirectory(std::move(levelDirectory)) {};

        void onInit(Context &context) override;

        void onUpdate(Context &context) override;

    private:
        std::unique_ptr<Menu::Menu> menu;
        Menu::MenuRenderer menuRenderer;
        std::string levelDirectory;
        std::array<std::string,
                Variables::Visual::LevelSelection::ROWS * Variables::Visual::LevelSelection::COLUMNS> levels{""};
        Renderer::Graphics::RenderDevice* renderDevice;
    };
}