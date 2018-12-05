#include "ECS/Systems/BumpSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/PlayerComponent.h"
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
		if (boundingBoxComponent != nullptr) {
			auto currentPosition = entityManager->getComponent<PositionComponent>(entity.id);
			auto currentVelocity = entityManager->getComponent<VelocityComponent>(entity.id);

			if (currentPosition != nullptr && currentVelocity != nullptr) {

				auto & collisions = boundingBoxComponent->collidesWith;
				auto collisionsCopy = collisions;

				if (collisions.size() > 0) {
					const auto & currentBB = boundingBoxComponent->boundingBox;
					
					bool xCol = false;
					bool yCol = false;

					int forceX = 0;
					int forceY = 0;

					float x = currentPosition->x;
					float y = currentPosition->y;
					BoundingBox bbXMin = BoundingBox(currentBB);
					bbXMin.SetPosXY(x - currentVelocity->dx * context.deltaTime, y);
					BoundingBox bbYMin = BoundingBox(currentBB);
					bbYMin.SetPosXY(x, y - currentVelocity->dy * context.deltaTime);
					BoundingBox bbXYMin = BoundingBox(currentBB);
					bbXYMin.SetPosXY(x - currentVelocity->dx * context.deltaTime, y - currentVelocity->dy * context.deltaTime);

					for (auto& id : collisions) {
						auto colliderPosition = entityManager->getComponent<PositionComponent>(id);
						if (colliderPosition != nullptr) {
							
							//Various checks for collisions
							bool cx2 = currentPosition->x < colliderPosition->x && currentVelocity->dx > 0;
							bool cx1 = currentPosition->x > colliderPosition->x && currentVelocity->dx < 0;
							bool cy1 = currentPosition->y > colliderPosition->y && currentVelocity->dy < 0;
							bool cy2 = currentPosition->y < colliderPosition->y && currentVelocity->dy > 0;

							const auto &colliderBB = entityManager->getComponent<BoundingBoxComponent>(id)->boundingBox;

							auto currentX = currentBB.GetPosX();
							auto currentY = currentBB.GetPosY();
							auto colliderX = colliderBB.GetPosX();
							auto colliderY = colliderBB.GetPosY();

							float xColT = 0.0;
							float yColT = 0.0;

							auto x1 = std::abs((colliderX + colliderBB.GetEast()) - (currentX + currentBB.GetWest()));
							auto x2 = std::abs((currentX + currentBB.GetEast()) - (colliderX + colliderBB.GetWest()));
							auto y1 = std::abs((colliderY - colliderBB.GetSouth()) - (currentY - currentBB.GetNorth()));
							auto y2 = std::abs((colliderY - colliderBB.GetNorth()) - (currentY - currentBB.GetSouth()));

							if (currentPosition->x > colliderPosition->x) {
								xColT = std::abs((colliderX + colliderBB.GetEast()) - (currentX + currentBB.GetWest()));
							}
							else if (currentPosition->x < colliderPosition->x) {
								xColT = std::abs((currentX + currentBB.GetEast()) - (colliderX + colliderBB.GetWest()));
							}

							if (currentPosition->y > colliderPosition->y) {
								yColT = std::abs((colliderY - colliderBB.GetSouth()) - (currentY - currentBB.GetNorth()));
							}
							else if (currentPosition->y < colliderPosition->y) {
								yColT = std::abs((colliderY - colliderBB.GetNorth()) - (currentY - currentBB.GetSouth()));
							}

							//The side with the least amount of collision needs te be resolved
							if (xColT < yColT) {
								if ((cx1 || cx2)) {
									xCol = true;
								}
							}
							else if (yColT < xColT) {
								if ((cy1 || cy2)) {
									yCol = true;
									
								}
							}
							else {
								xCol = true;
								yCol = true;
							}
						}
					}

					//Based on the axis of the collision, the positions needs to be reset
					if (xCol && yCol) {
						if (CountCollisions(bbXMin, collisionsCopy) == 0) {
							currentPosition->x -= currentVelocity->dx*context.deltaTime;
							currentVelocity->dx = 0;
						}
						else if (CountCollisions(bbYMin, collisionsCopy) == 0) {
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
			auto & bb = bbComponent->boundingBox;
			if (aabbCollider.CheckCollision(currentBox, bb)) {
				count++;
			}
		}
	}
	return count;
}