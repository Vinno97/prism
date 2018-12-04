#pragma once

class LinearPathFinding {
public:
	LinearPathFinding(EntityManager &entityManager_) : entityManager(entityManager_) {}

private:
	EntityManager &entityManager;
};