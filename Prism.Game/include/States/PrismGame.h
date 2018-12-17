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

namespace States
{
class PrismGame : public Game
{
  public:
    explicit PrismGame(std::string levelPath) : levelPath(std::move(levelPath)){};
	void onInit(Context &context) override;
	void onUpdate(Context &context) override;
	void onEnter(Context & context) override;
	void onLeave(Context & context) override;
	void toggleNightmare(Context & context);
	bool isNightmare();

	std::string getLevel() const { return levelPath; }

  private:
	ECS::EntityManager entityManager;
	ECS::SystemManager systemManager;
	EntityFactory entityFactory;
	Menu::MenuRenderer menuRenderer;
	Menu::MenuBuilder menuBuilder;
	std::unique_ptr<Menu::Menu> menu;


	//Textcontrols
	Menu::TextControl* redResource{nullptr};
	Menu::TextControl* greenResource{nullptr};
	Menu::TextControl* blueResource{nullptr};
	Menu::TextControl* health{nullptr};
	Menu::TextControl* survivedTime{nullptr};
	Menu::TextControl* score{nullptr};
	Menu::TextControl* fps{nullptr};

	bool canPressEscape{false};
	bool canPressF3{false};
	bool showFPS{false};
	bool isNightmareMode{false};
	std::string levelPath{};
	void registerSystems(Context &context);
	void toggleFPS(Context &context);
	void loadAudio(Context &context) const;
	int Fps(Context &context);
};
}