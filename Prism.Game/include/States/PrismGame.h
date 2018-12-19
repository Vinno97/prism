#pragma once

#include "Game.h"
#include "Menu/MenuBuilder.h"
#include "Menu/MenuRenderer.h"
#include "Menu/Menu.h"
#include "Menu/TextControl.h"
#include "ECS/EntityManager.h"
#include "ECS/Systems/System.h"
#include "ECS/SystemManager.h"
#include "EntityFactory.h"
#include "State.h"
#include <memory>
#include "World/WorldLoader.h"

namespace States {
    class PrismGame : public Game {
    public:
        explicit PrismGame(std::string levelPath, bool nightmareMode) : levelPath(std::move(levelPath)),
                                                                        isNightmareMode(nightmareMode) {};

        void onInit(Context &context) override;

        void onUpdate(Context &context) override;

        void onEnter(Context &context) override;

        void onLeave(Context &context) override;

        bool isNightmare();

        std::string getLevel() const { return levelPath; }

    private:
        ECS::EntityManager entityManager;
        ECS::SystemManager systemManager;
        Menu::MenuRenderer menuRenderer;
        Menu::MenuBuilder menuBuilder;
        std::unique_ptr<Menu::Menu> menu;

        Menu::Control *healthImage{nullptr};
        Menu::Control *resourceImage{nullptr};

        //Textcontrols
        Menu::TextControl *redResource{nullptr};
        Menu::TextControl *greenResource{nullptr};
        Menu::TextControl *blueResource{nullptr};
        Menu::TextControl *health{nullptr};
        Menu::TextControl *survivedTime{nullptr};
        Menu::TextControl *score{nullptr};
        Menu::TextControl *fps{nullptr};

        bool suspense_not_playing{true};
        bool canPressEscape{false};
        bool canPressF3{false};
        bool showFPS{false};
        bool isNightmareMode{false};
        std::string levelPath{};

        void registerSystems(Context &context);

        void changeTextColorNM();

        void toggleFPS(Context &context);

        void toggleResources(Context &context, int playerHealth);

        void loadAudio(Context &context) const;

        int Fps(Context &context);
    };
}
