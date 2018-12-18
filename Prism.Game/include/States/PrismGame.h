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
	PrismGame() = default;
	ECS::EntityManager entityManager;
	void onInit(Context &context) override;
	void onUpdate(Context &context) override;
	void onEnter(Context & context) override;
	void onLeave(Context & context) override;
	void toggleNightmare(Context & context);
	bool isNightmare();

  private:
	ECS::SystemManager systemManager;
	EntityFactory entityFactory;
	Menu::MenuRenderer menuRenderer;
	Menu::MenuBuilder menuBuilder;
	std::unique_ptr<Menu::Menu> menu;
	bool suspense_not_playing = true;

	//Textcontrols
	Menu::TextControl* redResource;
	Menu::TextControl* greenResource;
	Menu::TextControl* blueResource;
	Menu::TextControl* health;
	Menu::TextControl* survivedTime;
	Menu::TextControl* score;
	Menu::TextControl* fps;

	bool canPressEscape;
	bool canPressF3;
	bool showFPS;
	bool isNightmareMode;
	void registerSystems(Context &context);
	void toggleFPS(Context &context);
	void loadAudio(Context &context) const;
	int Fps(Context &context);
};
}