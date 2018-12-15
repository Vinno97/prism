#include "ECS/Systems/BumpSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/DynamicComponent.h"



#include "ECS/Components/BuildComponent.h"
#include "ECS/Components/ProjectileAttackComponent.h"
#include "ECS/Components/EnemyComponent.h"

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
		if(boundingBoxComponent != nullptr){
			auto & collisions = boundingBoxComponent->collidesWith;


			if (collisions.size() > 0) {
				auto currentPosition = entityManager->getComponent<PositionComponent>(entity.id);
				auto currentVelocity = entityManager->getComponent<VelocityComponent>(entity.id);
				if (currentPosition != nullptr && currentVelocity != nullptr) {
					const auto & currentBB = boundingBoxComponent->boundingBox;

					//Collision on x
					bool xCol = false;
					//Collision on y
					bool yCol = false;

					for (auto& colliderId : collisions) {
						if (entityManager->hasComponent<PositionComponent>(colliderId)) {
							auto colliderPosition = entityManager->getComponent<PositionComponent>(colliderId);


							if (entityManager->hasComponent<PlayerComponent>(entity.id)) {
								int k = 5;
							}

							//Various checks for collisions. Only in theses situations does the collisions need to be resolved
							bool cx2 = currentPosition->x < colliderPosition->x && currentVelocity->dx > 0;
							bool cx1 = currentPosition->x > colliderPosition->x && currentVelocity->dx < 0;
							bool cy1 = currentPosition->y > colliderPosition->y && currentVelocity->dy < 0;
							bool cy2 = currentPosition->y < colliderPosition->y && currentVelocity->dy > 0;

							const auto &colliderBB = entityManager->getComponent<BoundingBoxComponent>(colliderId)->boundingBox;

							//Depth of collision on x-axis
							float xColT = 0.0;
							//Depth of collision on y-axis
							float yColT = 0.0;

							if (currentPosition->x > colliderPosition->x) {
								xColT = std::abs((colliderBB.GetEastCoordinate()) - (currentBB.GetWestCoordinate()));
							}
							else if (currentPosition->x < colliderPosition->x) {
								xColT = std::abs((currentBB.GetEastCoordinate()) - (colliderBB.GetWestCoordinate()));
							}

							if (currentPosition->y > colliderPosition->y) {
								yColT = std::abs((colliderBB.GetNorthCoordinate()) - (currentBB.GetSouthCoordinate()));
								
							}
							else if (currentPosition->y < colliderPosition->y) {
								yColT = std::abs((colliderBB.GetSouthCoordinate()) - (currentBB.GetNorthCoordinate()));
							}

							//The side with the least amount of collision needs te be resolved
							if (xColT > 0 && yColT > 0) {
								if (xColT < yColT && (cx1 || cx2)) {
									xCol = true;
								}
								else if (yColT < xColT && (cy1 || cy2)) {
									yCol = true;
								}
								else if (xColT == yColT) {
									xCol = true;
									yCol = true;
								}
							}
							else if (xColT > 0 && yColT <= 0) {
								xCol = true;
							}
							else if (yColT > 0 && xColT <= 0) {
								yCol = true;
							}
						}
					}

					

					//Based on the axis of the collision, the positions needs to be reset
					if (xCol && yCol) {
						//Rare case of multicollision try to fix with only one step
						float x = currentPosition->x;
						float y = currentPosition->y;
						BoundingBox bbXMin = BoundingBox(currentBB);
						bbXMin.SetPosXY(x - currentVelocity->dx * context.deltaTime, y);
						BoundingBox bbYMin = BoundingBox(currentBB);
						bbYMin.SetPosXY(x, y - currentVelocity->dy * context.deltaTime);
						BoundingBox bbXYMin = BoundingBox(currentBB);
						bbXYMin.SetPosXY(x - currentVelocity->dx * context.deltaTime, y - currentVelocity->dy * context.deltaTime);
						if (CountCollisions(bbXMin, collisions) == 0) {
							currentPosition->x -= currentVelocity->dx*context.deltaTime;
							currentVelocity->dx = 0;
						}
						else if (CountCollisions(bbYMin, collisions) == 0) {
							currentPosition->y -= currentVelocity->dy*context.deltaTime;
							currentVelocity->dy = 0;
						}
						else {
							currentPosition->x -= currentVelocity->dx*context.deltaTime;
							currentVelocity->dx = 0;
							currentPosition->y -= currentVelocity->dy*context.deltaTime;
							currentVelocity->dy = 0;
						}
					}
					else if (xCol) {
						currentPosition->x -= currentVelocity->dx*context.deltaTime;
						currentVelocity->dx = 0;
					}
					else if (yCol) {
						currentPosition->y -= currentVelocity->dy*context.deltaTime;
						currentVelocity->dy = 0;
					}
				}
			}
		}
	}
}

int BumpSystem::CountCollisions(const BoundingBox &currentBox, const std::vector<unsigned int> &vector) const
{
	int count = 0;
	for (const auto& entity : vector) {
		auto bbComponent = entityManager->getComponent<BoundingBoxComponent>(entity);
		if (bbComponent != nullptr) {
			auto& bb = bbComponent->boundingBox;
			if (aabbCollider.CheckCollision(currentBox, bb)) {
				count++;
			}
		}
	}
	return count;
}