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
			auto & collisions = boundingBoxComponent->collidesWith;

			if (collisions.size() > 0) {
				const auto & currentBB = boundingBoxComponent->boundingBox;
				auto currentPosition = entityManager->getComponent<PositionComponent>(entity.id);
				auto currentVelocity = entityManager->getComponent<VelocityComponent>(entity.id);

				bool xCol = false;
				bool yCol = false;

				int forceX = 0;
				int forceY = 0;

				for (auto& id : collisions) {
					if (entityManager->hasComponent<PositionComponent>(id)) {
						auto colliderPosition = entityManager->getComponent<PositionComponent>(id);

						//Various checks for collisions
						bool cx2 = currentPosition->x < colliderPosition->x && currentVelocity->dx > 0;
						bool cx1 = currentPosition->x > colliderPosition->x && currentVelocity->dx < 0;
						bool cy1 = currentPosition->y > colliderPosition->y && currentVelocity->dy < 0;
						bool cy2 = currentPosition->y < colliderPosition->y && currentVelocity->dy > 0;
						
						
						//bool cx1 = currentPosition->x > colliderPosition->x;
						//bool cx2 = currentPosition->x < colliderPosition->x;
						//bool cy1 = currentPosition->y > colliderPosition->y;
						//bool cy2 = currentPosition->y < colliderPosition->y;
						//
						//if (collisions.size() > 1) {
						//	if (cx1) {
						//		forceX++;
						//	}
						//	else if (cx2) {
						//		forceX--;
						//	}
						//
						//	if (cy1) {
						//		forceY++;
						//	}
						//	else if (cy2) {
						//		forceY--;
						//	}
						//}
						//lse {
						//	auto &colliderBB = entityManager->getComponent<BoundingBoxComponent>(id)->boundingBox;
						//
						//	auto currentX = currentBB.GetPosX();
						//	auto currentY = currentBB.GetPosY();
						//	auto colliderX = colliderBB.GetPosX();
						//	auto colliderY = colliderBB.GetPosY();
						//
						//	//Calculate total collision on each axis
						//	float xColT = 0.0;
						//	float yColT = 0.0;
						//
						//	if (cx1) {
						//		xColT = std::abs((colliderX + colliderBB.GetEast()) - (currentX + currentBB.GetWest()));
						//	}
						//	else if (cx2) {
						//		xColT = std::abs((currentX + currentBB.GetEast()) - (colliderX + colliderBB.GetWest()));
						//	}
						//
						//	if (cy1) {
						//		yColT = std::abs((colliderY - colliderBB.GetSouth()) - (currentY - currentBB.GetNorth()));
						//	}
						//	else if (cy2) {
						//		yColT = std::abs((colliderY - colliderBB.GetNorth()) - (currentY - currentBB.GetSouth()));
						//	}
						//
						//	//The side with the least amount of collision needs te be resolved
						//	if (xColT <= yColT) {
						//		if (currentX > colliderX) {
						//			forceX++;
						//		}
						//		else {
						//			forceX--;
						//		}
						//	}
						//	if (yColT <= xColT) {
						//		if (currentY > colliderY) {
						//			forceY++;
						//		}
						//		else{
						//			forceY--;
						//		}
						//	}
						//	/*else {
						//		forceX++;
						//		forceY++;
						//	}*/
						//	int k = 9;
						//


						/*
						if (!(cx1 || cx2 || cy1 || cy2)) {
							collisionsCopy.erase(std::remove(collisionsCopy.begin(), collisionsCopy.end(), id), collisionsCopy.end());
						}*/

						
						//If collisions on both axis, determine axis of collision
						if ((cx1 || cx2) && (cy1 || cy2)) {
							auto &colliderBB = entityManager->getComponent<BoundingBoxComponent>(id)->boundingBox;

							auto currentX = currentBB.GetPosX();
							auto currentY = currentBB.GetPosY();
							auto colliderX = colliderBB.GetPosX();
							auto colliderY = colliderBB.GetPosY();

							//Calculate total collision on each axis
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

							//The side with the least amount of collision needs te be resolved
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
						}
						else if (cy1 || cy2) {
							yCol = true;
						}
					}
				}
				/*
				if ((forceX == 0 && forceY == 0)) {
					std::cout << "WAHT";
				}

				else if ((forceX == 0 && forceY == 0) || (forceX != 0 && forceY != 0)) {
					currentPosition->x -= currentVelocity->dx*context.deltaTime;
					currentVelocity->dx = 0;
					currentPosition->y -= currentVelocity->dy*context.deltaTime;
					currentVelocity->dy = 0;
				}
				else if (forceX != 0 && forceX*currentVelocity->dx < 0) {
					currentPosition->x -= currentVelocity->dx*context.deltaTime;
					currentVelocity->dx = 0;
				}
				else if (forceY != 0 && forceY*currentVelocity->dy < 0) {
					currentPosition->y -= currentVelocity->dy*context.deltaTime;
					currentVelocity->dy = 0;
				}
				else {
					std::cout << "WAHT";
				}
				*/

				/*
				float x = currentPosition->x;
				float y = currentPosition->y;
				BoundingBox bbXMin = BoundingBox(currentBB);
				bbXMin.SetPosXY(x - currentVelocity->dx * context.deltaTime, y);
				BoundingBox bbYMin = BoundingBox(currentBB);
				bbYMin.SetPosXY(x, y - currentVelocity->dx * context.deltaTime);
				int i1 = CountCollisions(bbXMin, collisions);
				int i2 = CountCollisions(bbYMin, collisions);

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
				}*/

				
				//Based on the axis of the collision, the positions needs to be reset
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
			}
		}
	}
}

int BumpSystem::CountCollisions(const BoundingBox &currentBox, const std::vector<unsigned int> &vector) const
{
	int count = 0;
	for (const auto& entity : vector) {
		if (entityManager->hasComponent<BoundingBoxComponent>(entity)) {
			auto& bb = entityManager->getComponent<BoundingBoxComponent>(entity)->boundingBox;
			if (aabbCollider.CheckCollision(currentBox, bb)) {
				count++;
			}
		}
	}
	return count;
}