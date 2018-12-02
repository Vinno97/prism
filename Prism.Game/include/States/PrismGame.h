#pragma once
#include "Game.h"
#include "Menu/MenuBuilder.h"
#include "Menu/MenuRenderer.h"
#include "Menu/Menu.h"
#include "ECS/EntityManager.h"
#include "ECS/Systems/System.h"
#include "ECS/SystemManager.h"
#include "EntityFactory.h"
#include "State.h"


namespace States
{
class PrismGame : public Game
{
  public:
	PrismGame() = default;
	void onInit(Context &context) override;
	void onUpdate(Context &context) override;
	void onEnter(Context & context) override;
	void onLeave() override;

  private:
	ECS::EntityManager entityManager;
	ECS::SystemManager systemManager;
	EntityFactory entityFactory;
	Menu::MenuBuilder menuBuilder;
	Menu::MenuRenderer menuRenderer;
	std::unique_ptr<ECS::System> gameOverSystem;
	Menu::Menu menu;
	void cheat(Context &context);
	bool canPressEscape;
	void registerSystems(Context &context);
	void loadAudio(Context &context) const;
};
} // namespace States