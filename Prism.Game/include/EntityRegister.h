#pragma once
#include <memory>

#include "ECS/Entity.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"

#include "ECS/Systems/MotionSystem.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/RenderSystem.h"

#include "ECS/Components/Component.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"

#include "Renderer/Graphics/Loader/ModelLoader.h"


class EntityRegister {
public: 
	EntityRegister();
	void RegisterPlayer(std::shared_ptr<EntityManager> entityManager);
	~EntityRegister();
};