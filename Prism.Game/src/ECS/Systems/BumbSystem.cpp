#include "ECS/Systems/BumbSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Physics;

BumbSystem::BumbSystem(EntityManager &entityManager) : System(entityManager) {}

BumbSystem::~BumbSystem()
= default;

void BumbSystem::update(Context context)
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>()) {
		auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);
		if (entityManager->hasComponent<VelocityComponent>(entity.id) && boundingBoxComponent->didCollide) {


			const auto boundingBox = &boundingBoxComponent->boundingBox;
			auto vector = &boundingBoxComponent->collidesWith;
			
			if (boundingBoxComponent->didCollide) {
				const auto position = entityManager->getComponent<PositionComponent>(entity.id);
				auto velocity = entityManager->getComponent<VelocityComponent>(entity.id);

				BoundingBox testBox1(*boundingBox);
				BoundingBox testBox2(*boundingBox);
				float x = position->x;
				float y = position->y;

				testBox1.SetPosXY(x -= velocity->dx*context.deltaTime, y);
				testBox2.SetPosXY(x, y -= velocity->dy*context.deltaTime);

				if (aabbCollider.AmountCollisions(testBox1, *boundingBox, *vector) == 0) {
					position->x -= velocity->dx*context.deltaTime;
					velocity->dx = 0;
				}
				else if (aabbCollider.AmountCollisions(testBox2, *boundingBox, *vector) == 0) {
					position->y -= velocity->dy*context.deltaTime;
					velocity->dy = 0;
				}
				else {
					position->x -= velocity->dx*context.deltaTime;
					velocity->dx = 0;
					position->y -= velocity->dy*context.deltaTime;
					velocity->dy = 0;

				}
			}
		}
	}
}

ECS::Systems::System* BumbSystem::clone()
{
	return new BumbSystem(*entityManager);
}


