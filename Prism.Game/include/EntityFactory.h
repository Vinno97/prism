#pragma once
#include "ECS/EntityManager.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Enums/ResourceTypeEnum.h"

class EntityFactory {
public:
	unsigned createPlayer(ECS::EntityManager& entityManager) const;
	unsigned createPlayer(unsigned entity, ECS::EntityManager& entityManager) const;

	unsigned createEnemy(ECS::EntityManager& entityManager) const;
	unsigned createEnemy(unsigned entity, ECS::EntityManager& entityManager) const;

	unsigned createResourcePoint(ECS::EntityManager & entityManager, Enums::ResourceType type, int gatherRate, float value) const;
	unsigned createResourcePoint(unsigned entity, ECS::EntityManager & entityManager, Enums::ResourceType type, int gatherRate, float value) const;

	unsigned createTower(ECS::EntityManager& entityManager) const;
	unsigned createTower(unsigned entity, ECS::EntityManager& entityManager) const;

	unsigned createWall(ECS::EntityManager& entityManager) const;
	unsigned createWall(unsigned entity, ECS::EntityManager& entityManager) const;

	unsigned createMine(ECS::EntityManager& entityManager) const;
	unsigned createMine(unsigned entity, ECS::EntityManager& entityManager) const;

	unsigned createScene(ECS::EntityManager & entityManager) const;
	static unsigned createScene(unsigned entity, ECS::EntityManager & entityManager);

	unsigned createProjectile(ECS::EntityManager & entityManager) const;
	unsigned createProjectile(unsigned entity, ECS::EntityManager & entityManager) const;
	
	unsigned createEnemySpawn(ECS::EntityManager & entityManager, float spawnInterval, bool enabled) const;
	unsigned createEnemySpawn(unsigned entity, ECS::EntityManager & entityManager, float spawnInterval, bool enabled) const;

	unsigned createFloor(ECS::EntityManager & entityManager) const;
	unsigned createFloor(unsigned entity, ECS::EntityManager & entityManager) const;

	unsigned createResourceBlob(ECS::EntityManager & entityManager, Enums::ResourceType type, float value) const;
	unsigned createResourceBlob(unsigned entity, ECS::EntityManager & entityManager, Enums::ResourceType type, float value) const;

	unsigned createCamera(ECS::EntityManager & entityManager);
	unsigned createCameraPointer(ECS::EntityManager & entityManager);
private:
	Renderer::Graphics::Loader::ModelLoader moderLoader;
};
