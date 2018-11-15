#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Physics;

CollisionSystem::CollisionSystem(EntityManager &entityManager,float width, float height, float posX, float posY, unsigned int maxObject) : System(entityManager)
{
	quadTree = QuadTree(width, height, posX, posY, maxObject);
}

CollisionSystem::~CollisionSystem()
= default;

void CollisionSystem::update(Context context)
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<ECS::Components::BoundingBoxComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id)) {
			auto boundingBox = &entityManager->getComponent<BoundingBoxComponent>(entity.id)->boundingBox;
			auto position = entityManager->getComponent<PositionComponent>(entity.id);
			boundingBox->SetPosXY(position->x, position->y);
			quadTree.Insert(*boundingBox);
		}
	}
	
	for (auto entity : entityManager->getAllEntitiesWithComponent<ECS::Components::BoundingBoxComponent>())
	{

		if (entityManager->hasComponent<PositionComponent>(entity.id)) {
			auto positionComponent = entityManager->getComponent<PositionComponent>(entity.id);
			auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);
			boundingBoxComponent->boundingBox.SetPosXY(positionComponent->x, positionComponent->y);

			std::vector<Physics::BoundingBox const *> vector;
			quadTree.RetrieveAll(vector,boundingBoxComponent->boundingBox);
			for (int i = 0;i < vector.size();i++) {
				if (&boundingBoxComponent->boundingBox != vector[i] && aabbCollider.CheckCollision(boundingBoxComponent->boundingBox, *vector[i])) {
					boundingBoxComponent->didCollide = true;
					boundingBoxComponent->collidesWith.push_back(vector[i]);
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

	return new CollisionSystem(*entityManager,width,height,b.GetPosX(),b.GetPosY(),quadTree.GetMaxObject());
}