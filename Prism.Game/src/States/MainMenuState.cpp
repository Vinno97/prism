#include "States/MainMenuState.h"
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "States/CreditsState.h"
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "States/CreditsState.h"
#include "States/HighScoreState.h"
#include "States/HelpState.h"
#include "States/LevelSelectionState.h"
#include "States/SaveSelectionState.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Util/AdvertisementSystem.h"
#include "States/ResolutionMenuState.h"
#include "Variables.h"

namespace States {

    using namespace Variables::Resources;
    using namespace Variables::Visual::MainMenu;

    void MainMenuState::onInit(Context &context) {
        loadMusic(context);
        context.stateMachine->addState<CreditsState>(context);
        context.stateMachine->addState<ResolutionMenuState>(context);
        context.stateMachine->addState<HelpState>(context);
        context.stateMachine->addState<HighScoreState>(context);

        std::function<void()> callback = [&context]() {
            if (!context.stateMachine->hasState<LevelSelectionState>()) {
                context.stateMachine->addState<LevelSelectionState>(context);
            }
            context.stateMachine->setState<LevelSelectionState>(context);
        };

        std::function<void()> loadCallback = [&context]() {
            if (!context.stateMachine->hasState<SaveSelectionState>()) {
                context.stateMachine->addState<SaveSelectionState>(context);
            }
            context.stateMachine->setState<SaveSelectionState>(context);
        };

        std::function<void()> creditsCallback = [&context]() { context.stateMachine->setState<CreditsState>(context); };
        std::function<void()> settingsCallback = [&context]() {
            context.stateMachine->setState<ResolutionMenuState>(context);
        };
        std::function<void()> helpCallback = [&]() { context.stateMachine->setState<HelpState>(context); };
        std::function<void()> highscoreCallback = [&context]() {
            context.stateMachine->setState<HighScoreState>(context);
        };
        std::function<void()> quitCallback = [&]() {
            if (exitBool) {
                exit(0);
            }
            exitBool = true;
        };

        const float aspect = float(context.window->width) / float(context.window->height);

        const auto btnHeight = MENU_HEIGHT * aspect;
        auto y = .7f;
        auto s = MENU_MARGIN + MENU_HEIGHT;

        menuBuilder.addControl(-0.35f, y -= s, MENU_WIDTH, btnHeight, Sprites::MainMenu::NEW_GAME, callback);
        menuBuilder.addControl(-0.35f, y -= s, MENU_WIDTH, btnHeight, Sprites::MainMenu::LOAD_SAVE, loadCallback);
        menuBuilder.addControl(-0.35f, y -= s, MENU_WIDTH, btnHeight, Sprites::MainMenu::CREDITS, creditsCallback);
        menuBuilder.addControl(-0.35f, y -= s, MENU_WIDTH, btnHeight, Sprites::MainMenu::HELP, helpCallback);
        menuBuilder.addControl(-0.35f, y -= s, MENU_WIDTH, btnHeight, Sprites::MainMenu::HIGHSCORE, highscoreCallback);
        menuBuilder.addControl(-0.35f, y -= s, MENU_WIDTH, btnHeight, Sprites::MainMenu::QUIT, quitCallback);
        menuBuilder.addControl(-0.98f, 0.9, 0.05, 0.05f * aspect, Sprites::MainMenu::SETTINGS, settingsCallback);

        menu = menuBuilder.buildMenu();

        renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
        renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
    }

    void MainMenuState::onUpdate(Context &context) {
        renderDevice->clearScreen();
        menuRenderer.renderMenu(*menu, context.window->width, context.window->height);

        auto input = context.inputManager;
        menu->handleInput(*context.inputManager, context.window->width, context.window->height);

        context.window->swapScreen();
    }

    void MainMenuState::onEnter(Context &context) {
        context.audioManager->playMusic("MainMenu");
    }

    void MainMenuState::loadMusic(Context &context) {
        context.audioManager->addMusic("MainMenu", "MainMenu.wav");
        context.audioManager->addSound("NightmareOn", "NightmareModeOn.wav");
        context.audioManager->addSound("NightmareOff", "NightmareModeOff.wav");
    }
}
