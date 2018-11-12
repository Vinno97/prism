#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"

CollisionSystem::CollisionSystem(ECS::EntityManager &entityManager,float width, float height, float posX, float posY) : System(entityManager)
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
		if (entityManager->hasComponent<ECS::Components::PositionComponent>(entity.id)) {
			auto boundingBox = entityManager->getComponent<BoundingBoxComponent>(entity.id)->boundingBox;
			auto Position = entityManager->getComponent<ECS::Components::PositionComponent>(entity.id);

			boundingBox.SetPosXY(Position->x, Position->y);
			quadTree.Insert(boundingBox);
		}
	}
	
	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>())
	{
		if (entityManager->hasComponent<ECS::Components::PositionComponent>(entity.id) 
			&& entityManager->hasComponent<ECS::Components::VelocityComponent>(entity.id)) {
			
			auto boundingBox = entityManager->getComponent<BoundingBoxComponent>(entity.id)->boundingBox;
			auto Position = entityManager->getComponent<ECS::Components::PositionComponent>(entity.id);
			auto Velocity = entityManager->getComponent<ECS::Components::VelocityComponent>(entity.id);

			boundingBox.SetPosXY(Position->x, Position->y);
			std::vector<BoundingBox const *> vector;
			quadTree.Retrieve(vector, boundingBox);


			for (auto &otherBox : vector) {
				if (otherBox != &boundingBox) {

					BoundingBox testBox(boundingBox);
					float x = boundingBox.GetPosX();
					float y = boundingBox.GetPosY();

					testBox.SetPosXY(x -= Velocity->dx*context.deltaTime, y);
					if (!aabbCollider.CheckCollision(*otherBox, testBox) && aabbCollider.CheckCollision(*otherBox, boundingBox)) {
						Position->x -= Velocity->dx*context.deltaTime;
						Velocity->dx = 0;
						boundingBox.SetPosXY(Position->x, y);
					}

					testBox.SetPosXY(x, y -= Velocity->dy*context.deltaTime);
					if (!aabbCollider.CheckCollision(*otherBox, testBox) && aabbCollider.CheckCollision(*otherBox, boundingBox)) {
						Position->y -= Velocity->dy*context.deltaTime;
						Velocity->dy = 0;
					}
				}
			}
		}
		quadTree.Clear();
	}
}

ECS::Systems::System* CollisionSystem::clone()
{
	BoundingBox b = quadTree.GetBounds();
	float width = b.GetEast() - b.GetWest();
	float height = b.GetNorth() - b.GetSouth();

	return new CollisionSystem(*entityManager,width,height,b.GetPosX(),b.GetPosY());
}
