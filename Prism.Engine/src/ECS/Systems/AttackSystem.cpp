#include <math.h>
#include "ECS/Systems/AttackSystem.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/HealthComponent.h"

ECS::Systems::AttackSystem::AttackSystem(std::shared_ptr<EntityManager> entityManager) : System(entityManager) {}

ECS::Systems::AttackSystem::~AttackSystem()
= default;

void ECS::Systems::AttackSystem::Attack(Context context)
{
	// TODO

}
