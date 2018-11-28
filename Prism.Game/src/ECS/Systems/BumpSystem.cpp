#include "ECS/Systems/BumpSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Physics;

BumpSystem::BumpSystem(EntityManager &entityManager) : System(entityManager) {}

BumpSystem::~BumpSystem()
= default;

void BumpSystem::update(Context& context)
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>()) {
		auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);
		if (entityManager->hasComponent<VelocityComponent>(entity.id) && boundingBoxComponent->didCollide) {


			const auto boundingBox = &boundingBoxComponent->boundingBox;
			auto vector = &boundingBoxComponent->collidesWith;
			
			if (boundingBoxComponent->didCollide) {
				const auto position = entityManager->getComponent<PositionComponent>(entity.id);
				auto velocity = entityManager->getComponent<VelocityComponent>(entity.id);

				//if (velocity->dx != 0.0 || velocity->dy != 0.0) {
					BoundingBox testBoxX(*boundingBox);
					BoundingBox testBoxY(*boundingBox);

					float x = position->x;
					float y = position->y;

					testBoxX.SetPosXY(x - velocity->dx*context.deltaTime, y);
					testBoxY.SetPosXY(x, y - velocity->dy*context.deltaTime);

					if (CountCollisions(testBoxX, *vector) == 0) {
						position->x -= velocity->dx*context.deltaTime;
						velocity->dx = 0;
					}
					else if (CountCollisions(testBoxY, *vector) == 0) {
						position->y -= velocity->dy*context.deltaTime;
						velocity->dy = 0;
					}
					else {
						position->x -= velocity->dx * context.deltaTime;
						velocity->dx = 0;
						position->y -= velocity->dy * context.deltaTime;
						velocity->dy = 0;
					}
				//}
				boundingBoxComponent->didCollide = false;
				boundingBoxComponent->collidesWith.clear();
			}
		}
	}
}


int BumpSystem::CountCollisions(BoundingBox &currentBox, std::vector<unsigned int> &vector)
{
	int count = 0;

	for (const auto& entity : vector) {
		if (entityManager->hasComponent<BoundingBoxComponent>(entity)) {
			auto bb = &entityManager->getComponent<BoundingBoxComponent>(entity)->boundingBox;
			if (aabbCollider.CheckCollision(currentBox, *bb)) {
				count++;
			}
		}
	}
	return count;
}

ECS::Systems::System* BumpSystem::clone()
{
	return new BumpSystem(*entityManager);
}
