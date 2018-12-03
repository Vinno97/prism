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


			const auto currentBoundingBox = &boundingBoxComponent->boundingBox;
			auto vector = &boundingBoxComponent->collidesWith;
			

			if (vector->size() > 0) {
				auto currentPosition = entityManager->getComponent<PositionComponent>(entity.id);
				auto currentVelocity = entityManager->getComponent<VelocityComponent>(entity.id);
				
				int total = 0;

				bool xCol = false;
				bool yCol = false;
				// tXcol = 0.0;
				//float tYcol = 0.0;

				for (auto& id : *vector) {	
					if (entityManager->hasComponent<PositionComponent>(id)) {
						auto colliderPosition = entityManager->getComponent<PositionComponent>(id);
						auto didColide = entityManager->getComponent<BoundingBoxComponent>(id)->didCollide;

						float colliderVelocityX = 0.0;
						float colliderVelocityY = 0.0;

						if (entityManager->hasComponent<VelocityComponent>(id)) {
							colliderVelocityX = entityManager->getComponent<VelocityComponent>(id)->dx;
							colliderVelocityY = entityManager->getComponent<VelocityComponent>(id)->dy;
						}

						bool cx1 = currentPosition->x > colliderPosition->x && currentVelocity->dx < 0;
						bool cx2 = currentPosition->x < colliderPosition->x && currentVelocity->dx > 0;
						bool cy1 = currentPosition->y > colliderPosition->y && currentVelocity->dy < 0;
						bool cy2 = currentPosition->y < colliderPosition->y && currentVelocity->dy > 0;


						if ((cx1 || cx2) && (cy1 || cy2)) {

							auto colliderBoundingBox = entityManager->getComponent<BoundingBoxComponent>(id)->boundingBox;
							auto currentX = currentPosition->x;
							auto currentY = currentPosition->y;
							auto colliderX = colliderPosition->x;
							auto colliderY = colliderPosition->y;

							float xColT = 0.0;
							float yColT = 0.0;

							if (cx1) {
								xColT = std::abs((colliderX + colliderBoundingBox.GetEast()) - (currentX + currentBoundingBox->GetWest()));
							}
							else if (cx2) {
								xColT = std::abs((currentX + currentBoundingBox->GetEast()) - (colliderX + colliderBoundingBox.GetWest()));
							}

							if (cy1) {
								yColT = std::abs((colliderY - colliderBoundingBox.GetSouth()) - (currentY - currentBoundingBox->GetNorth()));
							}
							else if (cy2) {
								yColT = std::abs((colliderY - colliderBoundingBox.GetNorth()) - (currentY - currentBoundingBox->GetSouth()));
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
							//total++;
						}

						else if (cx1 || cx2) {
							xCol = true;
							total++;
						}
						else if (cy1 || cy2) {//currentPosition->y > colliderPosition->y && currentVelocity->dy < 0) {
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
					/*
					BoundingBox testBoxPlusX(*boundingBox);
					BoundingBox testBoxPlusY(*boundingBox);

					//BoundingBox testBoxMinX(*boundingBox);
					//BoundingBox testBoxMinY(*boundingBox);
					//BoundingBox testBoxMinXPlusY(*boundingBox);
					//BoundingBox testBoxMinYPlusX(*boundingBox);

					float x = currentPosition->x;
					float y = currentPosition->y;

					testBoxPlusX.SetPosXY(x - currentVelocity->dx*context.deltaTime, y - currentVelocity->dy*context.deltaTime);
					testBoxPlusY.SetPosXY(x - currentVelocity->dx*context.deltaTime, y - currentVelocity->dy*context.deltaTime);

					//testBoxMinX.SetPosXY(x - currentVelocity->dx*context.deltaTime*1.5, y);
					//testBoxMinY.SetPosXY(x, y - currentVelocity->dy*context.deltaTime*1.5);
					//testBoxMinXPlusY.SetPosXY(x - currentVelocity->dx*context.deltaTime, y + currentVelocity->dy*context.deltaTime);
					//testBoxMinYPlusX.SetPosXY(x + currentVelocity->dx*context.deltaTime, y - currentVelocity->dy*context.deltaTime);

					//bool t1 = CountCollisions(testBoxMinXPlusY, *vector) == 0;
					//bool t2 = CountCollisions(testBoxMinYPlusX, *vector) == 0;

					//auto i1 = CountCollisions(testBoxXMin, *vector);
					//auto i2 = CountCollisions(testBoxYMin, *vector);

					int n = (vector->size() - total);
					//bool t1 = CountCollisions(testBoxMinX, *vector) - n == 0;
					//bool t2 = CountCollisions(testBoxMinY, *vector) - n == 0;
					
					//bool t1 = CountCollisions(testBoxMinX, *vector) == 0;
					//bool t2 = CountCollisions(testBoxMinY, *vector) == 0;

					bool t1 = CountCollisions(testBoxPlusX, *vector) == 0;
					bool t2 = CountCollisions(testBoxPlusY, *vector) == 0;

					if (t1) {
						currentPosition->x -= currentVelocity->dx*context.deltaTime;
						currentVelocity->dx = 0;
					}
					else if (t2) {
						currentPosition->y -= currentVelocity->dy*context.deltaTime;
						currentVelocity->dy = 0;
					}
					else {
						currentPosition->x -= currentVelocity->dx*context.deltaTime;
						currentVelocity->dx = 0;
						currentPosition->y -= currentVelocity->dy*context.deltaTime;
						currentVelocity->dy = 0;
					}
					if (tXcol < tYcol) {
						currentPosition->x -= currentVelocity->dx*context.deltaTime;
						currentVelocity->dx = 0;
					}
					else if (tYcol < tXcol) {
						currentPosition->y -= currentVelocity->dy*context.deltaTime;
						currentVelocity->dy = 0;
					}
					else {
						currentPosition->x -= currentVelocity->dx*context.deltaTime;
						currentVelocity->dx = 0;
						currentPosition->y -= currentVelocity->dy*context.deltaTime;
						currentVelocity->dy = 0;
					}*/
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

int ECS::Systems::BumpSystem::CountCollisionsX(unsigned int id, std::vector<unsigned int>& vector)
{
	int count = 0;
	const auto currentBox = entityManager->getComponent<BoundingBoxComponent>(id)->boundingBox;
	const auto currentVelocity = entityManager->getComponent<VelocityComponent>(id);

	for (const auto& entity : vector) {
		if (entityManager->hasComponent<BoundingBoxComponent>(entity)) {
			if (entityManager->hasComponent<VelocityComponent>(entity)) {
				const auto colliderBox = &entityManager->getComponent<BoundingBoxComponent>(entity)->boundingBox;
				const auto colliderVelocity = &entityManager->getComponent<BoundingBoxComponent>(entity)->boundingBox;

				const auto currentX = currentBox.GetPosX();
				const auto collideX = colliderBox->GetPosX();

				if (aabbCollider.CheckCollision(currentBox, *colliderBox) && (true)) {
					count++;
				}
			}
		}
	}
	return count;
}

int ECS::Systems::BumpSystem::CountCollisionsY(unsigned int id, std::vector<unsigned int>& vector)
{
	return 0;
}

