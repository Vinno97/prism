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

void BumpSystem::update(Context context)
{	
	for (auto entity : entityManager->getAllEntitiesWithComponent<VelocityComponent>()) {
		if (entityManager->hasComponent<BoundingBoxComponent>(entity.id)) {
			auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);
			if (boundingBoxComponent->didCollide) {


				const auto boundingBox = &boundingBoxComponent->boundingBox;
				auto vector = &boundingBoxComponent->collidesWith;

				if (CountCollisions(*boundingBox, *boundingBox, *vector) > 0) {
					const auto position = entityManager->getComponent<PositionComponent>(entity.id);
					auto velocity = entityManager->getComponent<VelocityComponent>(entity.id);

					BoundingBox testBox1(*boundingBox);
					BoundingBox testBox2(*boundingBox);
					float x = position->x;
					float y = position->y;

					testBox1.SetPosXY(x - velocity->dx*context.deltaTime, y);
					testBox2.SetPosXY(x, y - velocity->dy*context.deltaTime);

					if (CountCollisions(testBox1, *boundingBox, *vector) == 0) {
						position->x -= velocity->dx*context.deltaTime;
						velocity->dx = 0;
					}
					else if (CountCollisions(testBox2, *boundingBox, *vector) == 0) {
						position->y -= velocity->dy*context.deltaTime;
						velocity->dy = 0;
					}
					else {
						position->x -= velocity->dx * context.deltaTime;
						velocity->dx = 0;
						position->y -= velocity->dy * context.deltaTime;
						velocity->dy = 0;
					}
					boundingBoxComponent->didCollide = false;
					boundingBoxComponent->collidesWith.clear();
				}
			}
		}
	}
}

int BumpSystem::CountCollisions(BoundingBox &box1, BoundingBox &adress, std::vector<const BoundingBox*> &vector)
{
	int count = 0;
	for (int i = 0; i < vector.size();i++) {
		if (aabbCollider.CheckCollision(box1, *(vector[i]))) {
			count++;
		}
	}
	return count;
}

ECS::Systems::System* BumpSystem::clone()
{
	return new BumpSystem(*entityManager);
}


