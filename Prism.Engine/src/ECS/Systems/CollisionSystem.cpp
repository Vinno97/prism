#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Physics;

CollisionSystem::CollisionSystem(EntityManager &entityManager, float width, float height, float posX, float posY, unsigned int maxObject) : System(entityManager)
{
	quadTree = QuadTree(width, height, posX, posY, maxObject);
}

CollisionSystem::~CollisionSystem()
= default;

void CollisionSystem::update(Context& context)
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
			quadTree.Insert(*boundingBox);
		}
	}

	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id) /*&&
			entityManager->hasComponent<BoundingBoxComponent>(entity.id)*/) {

			auto positionComponent = entityManager->getComponent<PositionComponent>(entity.id);
			auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);

			boundingBoxComponent->didCollide = false;
			boundingBoxComponent->collidesWith.clear();

			std::vector<Physics::BoundingBox const *> boundingBoxes;
			quadTree.RetrieveAll(boundingBoxes, boundingBoxComponent->boundingBox);
			for (int i = 0; i < boundingBoxes.size(); i++) {
				if (&boundingBoxComponent->boundingBox != boundingBoxes[i] && aabbCollider.CheckCollision(boundingBoxComponent->boundingBox, *boundingBoxes[i])) {
					boundingBoxComponent->didCollide = true;
					boundingBoxComponent->collidesWith.push_back(boundingBoxMap[boundingBoxes[i]]);
				}
			}
		}
	}
	quadTree.Clear();
}

ECS::Systems::System* CollisionSystem::clone()
{
	BoundingBox b = quadTree.GetBounds();
	float width = b.GetEast() - b.GetWest();
	float height = b.GetNorth() - b.GetSouth();

	return new CollisionSystem(*entityManager, width, height, b.GetPosX(), b.GetPosY(), quadTree.GetMaxObject());
}