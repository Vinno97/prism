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
	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id)) {
			auto boundingBox = &entityManager->getComponent<BoundingBoxComponent>(entity.id)->boundingBox;
			auto Position = entityManager->getComponent<PositionComponent>(entity.id);

			boundingBox->SetPosXY(Position->x, Position->y);
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

			boundingBox->SetPosXY(position->x, position->y);
			std::vector<BoundingBox const *> vector;
			quadTree.Retrieve(vector, *boundingBox);


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
