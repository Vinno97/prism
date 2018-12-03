#include "ECS/Systems/BumpSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/DynamicComponent.h"

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Physics;

BumpSystem::BumpSystem(EntityManager &entityManager) : System(entityManager) {}

BumpSystem::~BumpSystem()
= default;

void BumpSystem::update(Context& context)
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<DynamicComponent>()) {
		auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);
		if (entityManager->hasComponent<VelocityComponent>(entity.id) && boundingBoxComponent->didCollide) {

			const auto & currentBB = boundingBoxComponent->boundingBox;
			auto & collisions = boundingBoxComponent->collidesWith;
			
			if (collisions.size() > 0) {
				auto currentPosition = entityManager->getComponent<PositionComponent>(entity.id);
				auto currentVelocity = entityManager->getComponent<VelocityComponent>(entity.id);
				
				int total = 0;

				bool xCol = false;
				bool yCol = false;

				for (auto& id : collisions) {
					if (entityManager->hasComponent<PositionComponent>(id)) {
						auto colliderPosition = entityManager->getComponent<PositionComponent>(id);

						bool cx1 = currentPosition->x > colliderPosition->x && currentVelocity->dx < 0;
						bool cx2 = currentPosition->x < colliderPosition->x && currentVelocity->dx > 0;
						bool cy1 = currentPosition->y > colliderPosition->y && currentVelocity->dy < 0;
						bool cy2 = currentPosition->y < colliderPosition->y && currentVelocity->dy > 0;

						if ((cx1 || cx2) && (cy1 || cy2)) {
							auto &colliderBB = entityManager->getComponent<BoundingBoxComponent>(id)->boundingBox;
							
							auto currentX = currentBB.GetPosX();
							auto currentY = currentBB.GetPosY();
							auto colliderX = colliderBB.GetPosX();
							auto colliderY = colliderBB.GetPosY();

							float xColT = 0.0;
							float yColT = 0.0;

							if (cx1) {
								xColT = std::abs((colliderX + colliderBB.GetEast()) - (currentX + currentBB.GetWest()));
							}
							else if (cx2) {
								xColT = std::abs((currentX + currentBB.GetEast()) - (colliderX + colliderBB.GetWest()));
							}

							if (cy1) {
								yColT = std::abs((colliderY - colliderBB.GetSouth()) - (currentY - currentBB.GetNorth()));
							}
							else if (cy2) {
								yColT = std::abs((colliderY - colliderBB.GetNorth()) - (currentY - currentBB.GetSouth()));
							}
							
							if (xColT < yColT) {
								xCol = true;
							}
							else if (yColT < xColT) {
								yCol = true;
							}
							else {
								xCol = true;
								yCol = true;
							}
						}

						else if (cx1 || cx2) {
							xCol = true;
							total++;
						}
						else if (cy1 || cy2) {
							yCol = true;
							total++;
						}
					}
				}
		
				if (xCol && yCol) {
					currentPosition->x -= currentVelocity->dx*context.deltaTime;
					currentVelocity->dx = 0;
					currentPosition->y -= currentVelocity->dy*context.deltaTime;
					currentVelocity->dy = 0;
				}
				else if (xCol) {
					currentPosition->x -= currentVelocity->dx*context.deltaTime;
					currentVelocity->dx = 0;
				} 
				else if (yCol) {
					currentPosition->y -= currentVelocity->dy*context.deltaTime;
					currentVelocity->dy = 0;
				}
				
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