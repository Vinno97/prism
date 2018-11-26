#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/DynamicComponent.h"
#include <list>

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Physics;

CollisionSystem::CollisionSystem(EntityManager &entityManager, float width, float height, float posX, float posY, unsigned int maxObject) : System(entityManager)
{
	dynamicQuadTree = QuadTree(width, height, posX, posY, maxObject);
	staticQuadTree = QuadTree(width, height, posX, posY, maxObject);
}

CollisionSystem::~CollisionSystem()
= default;

void ECS::Systems::CollisionSystem::registerStaticObjects()
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<ECS::Components::BoundingBoxComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id)) {
			auto boundingBox = &entityManager->getComponent<BoundingBoxComponent>(entity.id)->boundingBox;
			auto position = entityManager->getComponent<PositionComponent>(entity.id);

			boundingBox->SetPosXY(position->x, position->y);

			if (!entityManager->hasComponent<BoundingBoxComponent>(boundingBoxMap[boundingBox])) {
				boundingBoxMap[boundingBox] = entity.id;
			}
			staticQuadTree.Insert(*boundingBox);
		}
	}
}

void CollisionSystem::update(Context& context)
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>())//ECS::Components::DynamicComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id) && entityManager->hasComponent<BoundingBoxComponent>(entity.id)) {
			auto boundingBox = &entityManager->getComponent<BoundingBoxComponent>(entity.id)->boundingBox;
			auto position = entityManager->getComponent<PositionComponent>(entity.id);
			
			boundingBox->SetPosXY(position->x, position->y);

			if (!entityManager->hasComponent<BoundingBoxComponent>(boundingBoxMap[boundingBox])) {
				boundingBoxMap[boundingBox] = entity.id;
			}			
			dynamicQuadTree.Insert(*boundingBox);
		}
	}

	for (auto entity : entityManager->getAllEntitiesWithComponent<DynamicComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id) /*&&
			entityManager->hasComponent<BoundingBoxComponent>(entity.id)*/) {

			auto positionComponent = entityManager->getComponent<PositionComponent>(entity.id);
			auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);

			boundingBoxComponent->didCollide = false;
			boundingBoxComponent->collidesWith.clear();

			std::list<Physics::BoundingBox const *> boundingBoxes;

			dynamicQuadTree.RetrieveAll(boundingBoxes, boundingBoxComponent->boundingBox);
			//staticQuadTree.RetrieveAll(boundingBoxes, boundingBoxComponent->boundingBox);

			for (const auto& currentBox : boundingBoxes) {
				if (&boundingBoxComponent->boundingBox != currentBox && aabbCollider.CheckCollision(boundingBoxComponent->boundingBox, *currentBox)) {
					boundingBoxComponent->didCollide = true;
					boundingBoxComponent->collidesWith.push_back(boundingBoxMap[currentBox]);
				}
			}

			// for (int i = 0; i < boundingBoxes.size(); i++) {
			// 	if (&boundingBoxComponent->boundingBox != boundingBoxes[i] && aabbCollider.CheckCollision(boundingBoxComponent->boundingBox, *boundingBoxes[i])) {
			// 		boundingBoxComponent->didCollide = true;
			// 		boundingBoxComponent->collidesWith.push_back(boundingBoxMap[boundingBoxes[i]]);
			// 	}
			// }
		}
	}
	dynamicQuadTree.Clear();
}

ECS::Systems::System* CollisionSystem::clone()
{
	BoundingBox b = dynamicQuadTree.GetBounds();
	float width = b.GetEast() - b.GetWest();
	float height = b.GetNorth() - b.GetSouth();

	CollisionSystem *n = new CollisionSystem(*entityManager, width, height, b.GetPosX(), b.GetPosY(), dynamicQuadTree.GetMaxObject());
	n->registerStaticObjects();

	return n;
}