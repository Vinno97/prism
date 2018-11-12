#include <math.h>
#include "ECS/Systems/AttackSystem.h"
#include "ECS/EntityManager.h";
#include "ECS/SystemManager.h";
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "../../Prism.Game/include/ECS/Components/EnemyComponent.h"
#include "../../Prism.Game/include/ECS/Components/PlayerComponent.h"

using namespace ECS;
using namespace ECS::Components;

ECS::Systems::AttackSystem::AttackSystem(EntityManager &entityManager) : System(entityManager) { }

ECS::Systems::AttackSystem::~AttackSystem()
= default;


void ECS::Systems::AttackSystem::update(Context context) {
	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id) && (entityManager->hasComponent<HealthComponent>(entity.id))) {
			auto boundingBox = &entityManager->getComponent<BoundingBoxComponent>(entity.id)->boundingBox;
			auto Position = entityManager->getComponent<PositionComponent>(entity.id);

			boundingBox->SetPosXY(Position->x, Position->y);
			quadTree.Insert(*boundingBox);
		}
	}

	for (auto entity : entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>())
	{
		if (entityManager->hasComponent<PositionComponent>(entity.id)
			&& entityManager->hasComponent<HealthComponent>(entity.id)) {

			auto boundingBox = &entityManager->getComponent<BoundingBoxComponent>(entity.id)->boundingBox;
			auto Position = entityManager->getComponent<PositionComponent>(entity.id);

			boundingBox->SetPosXY(Position->x, Position->y);
			std::vector<BoundingBox const *> vec;
			quadTree.Retrieve(vec, *boundingBox);

			int count = 0;

			for (auto otherBox : vec) {
				count++;
				if (otherBox != boundingBox) {
					float x = boundingBox->GetPosX();
					float y = boundingBox->GetPosY();

					if (aabbCollider.CheckCollision(*otherBox, *boundingBox)) {
						if (entityManager->hasComponent<PlayerComponent>(entity.id)) {
							auto currentComponent = entityManager->getComponent<HealthComponent>(entity.id);
							currentComponent->health -= 10;

							if (currentComponent->health == 0) {
								std::cout << "Player is dead" << std::endl;
								entityManager->removeEntity(entity.id);
							}
							// Print health (Test)
							std::cout << "Speler: " << currentComponent->health << std::endl;
						}
						else if (entityManager->hasComponent<EnemyComponent>(entity.id)) {
							auto currentComponent = entityManager->getComponent<HealthComponent>(entity.id);
							entityManager->removeEntity(entity.id);				
							
							std::cout << "Enemy is exploded" << std::endl;
						
						}
					}
				}
			}
		}
	}
	quadTree.Clear();
}

System * ECS::Systems::AttackSystem::clone()
{
	BoundingBox b = quadTree.GetBounds();
	float width = b.GetEast() - b.GetWest();
	float height = b.GetNorth() - b.GetSouth();

	return new AttackSystem(*entityManager);
}
