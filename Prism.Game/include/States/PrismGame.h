#pragma once
#include "Game.h"
#include "Menu/MenuBuilder.h"
#include "Menu/MenuRenderer.h"
#include "Menu/Menu.h"
#include "Menu/TextControl.h"
#include "ECS/EntityManager.h"
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
	void onInit(Context &context) override;
	void onUpdate(Context &context) override;
	void onEnter() override;
	void onLeave() override;

  private:
	ECS::EntityManager entityManager;
	ECS::SystemManager systemManager;
	EntityFactory entityFactory;
	Menu::MenuRenderer menuRenderer;
	Menu::MenuBuilder menuBuilder;
	std::unique_ptr<Menu::Menu> menu;

	//Textcontrols
	Menu::TextControl* redResource;
	Menu::TextControl* greenResource;
	Menu::TextControl* blueResource;
	Menu::TextControl* health;
	Menu::TextControl* healthDot;
	Menu::TextControl* resourceRedDot;
	Menu::TextControl* resourceBlueDot;
	Menu::TextControl* resourceGreenDot;
	Menu::TextControl* fps;

	bool canPressEscape;
	bool canPressF3;
	bool showFPS;
	void registerSystems(Context &context);
	void toggleFPS(Context &context);
	void loadAudio(Context &context) const;
	int Fps(Context &context);
};
}