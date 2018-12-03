#pragma once
#include "Game.h"
#include "Menu/MenuBuilder.h"
#include "Menu/MenuRenderer.h"
#include "Menu/Menu.h"
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

	bool canPressEscape;
	void registerSystems(Context &context);
	void loadAudio(Context &context) const;
};
} // namespace States