#include "ECS/Systems/CollisionHandlerSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Physics;

CollisionHandlerSystem::CollisionHandlerSystem(EntityManager &entityManager) : System(entityManager)
{
}

CollisionHandlerSystem::~CollisionHandlerSystem()
= default;

void CollisionHandlerSystem::update(Context context)
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>()) {
		auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);
		if (entityManager->hasComponent<VelocityComponent>(entity.id) && boundingBoxComponent->didCollide) {


			const auto boundingBox = &boundingBoxComponent->boundingBox;
			auto vector = &boundingBoxComponent->collidesWith;
			
			if (AmountCollisions(*boundingBox, *boundingBox, *vector) > 0) {
				const auto position = entityManager->getComponent<PositionComponent>(entity.id);
				auto velocity = entityManager->getComponent<VelocityComponent>(entity.id);

				BoundingBox testBox1(*boundingBox);
				BoundingBox testBox2(*boundingBox);
				float x = position->x;
				float y = position->y;

				testBox1.SetPosXY(x -= velocity->dx*context.deltaTime, y);
				testBox2.SetPosXY(x, y -= velocity->dy*context.deltaTime);

				if (AmountCollisions(testBox1, *boundingBox, *vector) == 0) {
					position->x -= velocity->dx*context.deltaTime;
					velocity->dx = 0;
				}
				else if (AmountCollisions(testBox2, *boundingBox, *vector) == 0) {
					position->y -= velocity->dy*context.deltaTime;
					velocity->dy = 0;
				}
				else {
					position->x -= velocity->dx*context.deltaTime;
					velocity->dx = 0;
					position->y -= velocity->dy*context.deltaTime;
					velocity->dy = 0;

				}
				//boundingBox->SetPosXY(position->x, position->y);
			}
			boundingBoxComponent->didCollide = false;
			boundingBoxComponent->collidesWith.clear();
		}
	}
	/*
	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id)) {
			auto boundingBox = &entityManager->getComponent<BoundingBoxComponent>(entity.id)->boundingBox;
			auto position = entityManager->getComponent<PositionComponent>(entity.id);

			boundingBox->SetPosXY(position->x, position->y);
			quadTree.Insert(*boundingBox);
		}
	}
	
	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id)
			&& entityManager->hasComponent<VelocityComponent>(entity.id)) {
			
			auto boundingBox = &entityManager->getComponent<BoundingBoxComponent>(entity.id)->boundingBox;
			auto position = entityManager->getComponent<PositionComponent>(entity.id);
			auto velocity = entityManager->getComponent<VelocityComponent>(entity.id);

			//boundingBox->SetPosXY(position->x, position->y);
			std::vector<BoundingBox const *> vector;
			quadTree.RetrieveAll(vector, *boundingBox);
			if (vector.size() >= 3) {
				//std::cout<<"WHAT???????????";
			}

			if (AmountCollisions(*boundingBox, *boundingBox,vector) > 0) {
				BoundingBox testBox1(*boundingBox);
				BoundingBox testBox2(*boundingBox);
				float x = position->x;
				float y = position->y;

				testBox1.SetPosXY(x -= velocity->dx*context.deltaTime, y);
				testBox2.SetPosXY(x, y -= velocity->dy*context.deltaTime);

				if (AmountCollisions(testBox1, *boundingBox,vector) == 0) {
					position->x -= velocity->dx*context.deltaTime;
					velocity->dx = 0;
				}
				else if (AmountCollisions(testBox2, *boundingBox,vector) == 0) {
					position->y -= velocity->dy*context.deltaTime;
					velocity->dy = 0;
				}
				else {
					position->x -= velocity->dx*context.deltaTime;
					velocity->dx = 0;
					position->y -= velocity->dy*context.deltaTime;
					velocity->dy = 0;
					
				}
				boundingBox->SetPosXY(position->x, position->y);
			}

			/*
			for (auto otherBox : vector) {
				if (otherBox != boundingBox) {

					BoundingBox testBox(*boundingBox);
					float x = position->x;
					float y = position->y;

					testBox.SetPosXY(x -= velocity->dx*context.deltaTime, y);
					if (!aabbCollider.CheckCollision(*otherBox, testBox) && aabbCollider.CheckCollision(*otherBox, *boundingBox)) {
						position->x -= velocity->dx*context.deltaTime;
						velocity->dx = 0;
						boundingBox->SetPosXY(position->x, position->y);
					}

					testBox.SetPosXY(x, y -= velocity->dy*context.deltaTime);
					if (!aabbCollider.CheckCollision(*otherBox, testBox) && aabbCollider.CheckCollision(*otherBox, *boundingBox)) {
						position->y -= velocity->dy*context.deltaTime;
						velocity->dy = 0;
						boundingBox->SetPosXY(position->x, position->y);
					}
				}
			}
			*//*
		}
	}
	quadTree.Clear();
	*/
}

ECS::Systems::System* CollisionHandlerSystem::clone()
{
	return new CollisionHandlerSystem(*entityManager);
}

int ECS::Systems::CollisionHandlerSystem::AmountCollisions(BoundingBox &box1,BoundingBox &adress, std::vector<const BoundingBox*> &vector)
{
	int count = 0;
	for (int i = 0; i < vector.size();i++) {
		if (&adress != vector[i] && aabbCollider.CheckCollision(box1, *(vector[i]))) {
			count++;
		}
	}
	return count;
}
