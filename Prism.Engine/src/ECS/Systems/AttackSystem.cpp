#include <math.h>
#include "ECS/Systems/AttackSystem.h"
#include "ECS/EntityManager.h";
#include "ECS/SystemManager.h";
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "../../Prism.Game/include/ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"

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

			auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);
			auto Position = entityManager->getComponent<PositionComponent>(entity.id);

			boundingBoxComponent->boundingBox.SetPosXY(Position->x, Position->y);
			std::vector<Physics::BoundingBox const *> vec;
			quadTree.RetrieveAll(vec, boundingBoxComponent->boundingBox);

			for (int i = 0; i < vec.size(); i++) {
				if (&boundingBoxComponent->boundingBox != vec[i] && aabbCollider.CheckCollision(boundingBoxComponent->boundingBox, *vec[i])) {
					float x = boundingBoxComponent->boundingBox.GetPosX();
					float y = boundingBoxComponent->boundingBox.GetPosY();

					if (aabbCollider.CheckCollision(*vec[i], boundingBoxComponent->boundingBox)) {
						updateEntity(entity.id);
					}
				}
			}
		}
	}
	quadTree.Clear();
}

void ECS::Systems::AttackSystem::updateEntity(int id) {
	if (entityManager->hasComponent<PlayerComponent>(id)) {
		auto currentComponent = entityManager->getComponent<HealthComponent>(id);
		currentComponent->health -= 10;

		if (currentComponent->health == 0) {

			// Print (Remove after review)
			std::cout << "Player is dead" << std::endl;
			entityManager->removeEntity(id);
		}
		// Print (Remove after review)
		std::cout << "Speler: " << currentComponent->health << std::endl;
	}
	else if (entityManager->hasComponent<EnemyComponent>(id)) {
		entityManager->removeEntity(id);
		// Print (Remove after review)
		std::cout << "Enemy is exploded" << std::endl;
	}
}


ECS::System * ECS::Systems::AttackSystem::clone()
{
	Physics::BoundingBox b = quadTree.GetBounds();
	float width = b.GetEast() - b.GetWest();
	float height = b.GetNorth() - b.GetSouth();

	return new AttackSystem(*entityManager);
}
