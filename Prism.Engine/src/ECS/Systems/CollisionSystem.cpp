#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollidableComponent.h"
#include "ECS/Components/DynamicComponent.h"
#include <list>

using namespace ECS;
using namespace Components;
using namespace Systems;
using namespace Physics;

CollisionSystem::CollisionSystem(EntityManager &entityManager, float width, float height, float posX, float posY, unsigned int maxObject) : System(entityManager)
{
	quadTree = QuadTree(width, height, posX, posY, maxObject);
}

CollisionSystem::~CollisionSystem()
= default;


void CollisionSystem::update(Context& context)
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<CollidableComponent>())
	{
		auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);
		auto position = entityManager->getComponent<PositionComponent>(entity.id);
		if (boundingBoxComponent != nullptr && position != nullptr) {
			auto &boundingBox = boundingBoxComponent->boundingBox;

			boundingBox.SetPosXY(position->x, position->y);

			if (!entityManager->hasComponent<BoundingBoxComponent>(boundingBoxMap[&boundingBox])) {
				boundingBoxMap[&boundingBox] = entity.id;
			}
			quadTree.Insert(boundingBox);
		}
	}

	for (auto entity : entityManager->getAllEntitiesWithComponent<DynamicComponent>())
	{
		auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);
		auto position = entityManager->getComponent<PositionComponent>(entity.id);
		if (boundingBoxComponent != nullptr && position != nullptr) {
			boundingBoxComponent->didCollide = false;
			boundingBoxComponent->collidesWith.clear();
			boundingBoxComponent->boundingBox.SetPosXY(position->x, position->y);

			std::list<Physics::BoundingBox const *> boundingBoxes;
			quadTree.RetrieveAll(boundingBoxes, boundingBoxComponent->boundingBox);
			boundingBoxComponent->boundingBox.SetPosXYZ(position->x, position->y,position->z);

			for (const auto& currentBox : boundingBoxes) {
				auto k = aabbCollider.CheckCollision(boundingBoxComponent->boundingBox, *currentBox);
				if (&boundingBoxComponent->boundingBox != currentBox && aabbCollider.CheckCollision(boundingBoxComponent->boundingBox, *currentBox)) {
					boundingBoxComponent->didCollide = true;
					boundingBoxComponent->collidesWith.push_back(boundingBoxMap[currentBox]);
				}
			}
		}
	}
	quadTree.Clear();
}
