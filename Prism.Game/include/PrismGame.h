#pragma once

#include "Game.h"

#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"

#include "EntityRegister.h"

class PrismGame : public Game
{
public:
	PrismGame();
	void onInit(Context &context) override;
	void onUpdate(Context &context) override;
	void onEnter() override;
	void onLeave() override;
	~PrismGame();

private:
	std::shared_ptr<EntityManager> entityManager;
	std::shared_ptr<SystemManager> systemManager;
	std::shared_ptr<EntityRegister> entityRegister;
	void registerSystems(Context &context);
};
