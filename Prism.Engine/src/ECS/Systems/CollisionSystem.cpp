#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"

CollisionSystem::CollisionSystem(float width, float height, float posX, float posY, std::shared_ptr<ECS::EntityManager> entityManager) : System(entityManager)
{
	quadTree = QuadTree(width, height, posX, posY);
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update(Context context)
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>()) 
	{
		quadTree.Insert(entity.component->boundingBox);
		quadTree.Retrieve(entity.component->boundingBox);
	}


}
