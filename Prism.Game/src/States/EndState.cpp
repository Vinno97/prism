#include "States/EndState.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "States/MainMenuState.h"
#include "States/EndState.h"
#include "States/TransitionState.h"
#include "States/PauseState.h"
#include "States/MainMenuState.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/ScoreComponent.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Variables.h"

namespace States {
    using namespace ECS;
    using namespace ECS::Components;

    void EndState::onInit(Context &context) {
        std::function<void()> callbackMainMenu = [&context]() {
            context.stateMachine->removeState<PrismGame>();
            context.stateMachine->setState<MainMenuState>();
        };

        std::function<void()> callBackRestart = [&context]() {
            auto level = context.stateMachine->getState<PrismGame>()->getLevel();
            auto isNightmareMode = context.stateMachine->getState<PrismGame>()->isNightmare();
            context.stateMachine->removeState<PrismGame>();
            context.stateMachine->addState<PrismGame>(level, isNightmareMode);
            context.stateMachine->addState<TransitionState<PrismGame>>();
            context.stateMachine->setState<TransitionState<PrismGame>>();
        };

        menuBuilder.addControl(-0.5, 0.5, 1, 0.24, Variables::Resources::Sprites::GAME_OVER);
        menuBuilder.addControl(-0.45, -0.10, 0.005, 0.47, "img/score_bar.png");
        menuBuilder.addControl(0, -0.6, 0.7, 0.18, "img/mainMenuButton.png", callbackMainMenu);
        menuBuilder.addControl(-0.7, -0.6, 0.7, 0.18, "img/restart.png", callBackRestart);

        statsLabel = menuBuilder.addTextControl(-0.4, 0.32, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f}, "Score:");
        survivedTimeLabel = menuBuilder.addTextControl(-0.4, 0.25, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f},
                                                       "Time survived:");
        killedEnemiesLabel = menuBuilder.addTextControl(-0.4, 0.18, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f}, "Kills:");
        redLabel = menuBuilder.addTextControl(-0.4, 0.11, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f}, "Red resources:");
        blueLabel = menuBuilder.addTextControl(-0.4, 0.04, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f}, "Blue resources:");
        greenLabel = menuBuilder.addTextControl(-0.4, -0.03, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f},
                                                "Green resources:");
        scoreLabel = menuBuilder.addTextControl(-0.4, -0.10, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f}, "Total score:");

        survivedTime = menuBuilder.addTextControl(0.15, 0.25, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f}, "0");
        killedEnemies = menuBuilder.addTextControl(0.15, 0.18, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f}, "0");
        red = menuBuilder.addTextControl(0.15, 0.11, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f}, "0");
        blue = menuBuilder.addTextControl(0.15, 0.04, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f}, "0");
        green = menuBuilder.addTextControl(0.15, -0.03, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f}, "0");
        score = menuBuilder.addTextControl(0.15, -0.10, 0.0013, Math::Vector3f{0.1f, 0.1f, 0.1f}, "0");
        menu = menuBuilder.buildMenu();
        Renderer::Graphics::RenderDevice *renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
        renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
    }

    void EndState::onUpdate(Context &context) {
        score->text = std::to_string(totalscore);
        survivedTime->text = std::to_string(time);
        red->text = std::to_string(resourceRed);
        blue->text = std::to_string(resourceBlue);
        green->text = std::to_string(resourceGreen);
        killedEnemies->text = std::to_string(kills);
        Renderer::Graphics::RenderDevice *renderDevice = Renderer::Graphics::OpenGL::OGLRenderDevice::getRenderDevice();
        renderDevice->clearScreen();
        menuRenderer.renderMenu(*menu, context.window->width, context.window->height);

        menu->handleInput(context);

        context.window->swapScreen();
    }

    void EndState::onEnter(Context &context) {
        updateScores();
    }

    void EndState::updateScores() {
        std::fstream file;
        std::vector<int> numbers;
        int newScore = totalscore;
        std::string filename = "res/saves/scores.txt";

        file.open("res/saves/scores.txt");

        if (file.fail()) {
            numbers.push_back(newScore);
        } else {
            if (file.peek() == std::ifstream::traits_type::eof()) {
                numbers.push_back(newScore);
            } else {
                int count = 0;
                int num;
                while (file >> num) {
                    // Max 5 highscores
                    if (count == 5) {
                        break;
                    }

                    // Add newScore when it belongs to the highscores
                    if (newScore >= num) {
                        numbers.push_back(newScore);
                        newScore = 0;
                        count++;
                    }

                    // Add current highscores
                    if (count < 5) {
                        numbers.push_back(num);
                        count++;
                    }
                }

                if (count <= 4 && newScore != 0) {
                    numbers.push_back(newScore);
                }
            }
        }

        // Clear file scores.txt and copy values (vector: numbers) to file
        std::ofstream out("res/saves/scores.txt");
        if (out.is_open()) {
            std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(out, "\n"));
        }
    }

    void EndState::onLeave(Context &context) {
    }
}
