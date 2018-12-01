#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/PlacableComponent.h"
#include "ECS/Components/DynamicComponent.h"
#include <list>

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
	for (auto entity : entityManager->getAllEntitiesWithComponent<PlacableComponent>())//ECS::Components::DynamicComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id) && entityManager->hasComponent<BoundingBoxComponent>(entity.id)) {
			auto boundingBox = &entityManager->getComponent<BoundingBoxComponent>(entity.id)->boundingBox;
			auto position = entityManager->getComponent<PositionComponent>(entity.id);
			
			boundingBox->SetPosXY(position->x, position->y);

			if (!entityManager->hasComponent<BoundingBoxComponent>(boundingBoxMap[boundingBox])) {
				boundingBoxMap[boundingBox] = entity.id;
			}			
			quadTree.Insert(*boundingBox);
		}
	}

	for (auto entity : entityManager->getAllEntitiesWithComponent<DynamicComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id) &&
			entityManager->hasComponent<BoundingBoxComponent>(entity.id)) {

			auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);
			boundingBoxComponent->didCollide = false;
			boundingBoxComponent->collidesWith.clear();
			
			auto velocity = entityManager->getComponent<VelocityComponent>(entity.id);
			auto position = entityManager->getComponent<PositionComponent>(entity.id);
			auto testBox = boundingBoxComponent->boundingBox;
			testBox.SetPosXY(position->x + velocity->dx * context.deltaTime, position->y + velocity->dy * context.deltaTime);

			std::list<Physics::BoundingBox const *> boundingBoxes;
			quadTree.RetrieveAll(boundingBoxes, testBox);
			
			for (const auto& currentBox : boundingBoxes) {
				if (&boundingBoxComponent->boundingBox != currentBox && aabbCollider.CheckCollision(testBox, *currentBox)) {
					boundingBoxComponent->didCollide = true;
					boundingBoxComponent->collidesWith.push_back(boundingBoxMap[currentBox]);
				}
			}
		}
	}
	quadTree.Clear();
}
