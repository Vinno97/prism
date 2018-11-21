#pragma once

#include "Game.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "EntityFactory.h"
#include "State.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

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
	void cheat(Context &context);

  private:
	ECS::EntityManager entityManager;
	ECS::SystemManager systemManager;
	EntityFactory entityFactory;
	Menu::MenuBuilder menuBuilder;
	Menu::MenuRenderer menuRenderer;
	Menu::Menu menu;
	void registerSystems(Context &context);
	bool canPressEscape;
};
} // namespace States
